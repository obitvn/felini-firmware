/* logic analyzer sump example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"

#include "logic_analyzer_pin_definition.h"
#include "logic_analyzer_hal.h"

#include "logic_analyzer_const_definition.h"
#include "logic_analyzer_sump_definition.h"
#include "logic_analyzer_sump.h"

static int first_trigger_pin = 0;
static int first_trigger_val = 0;
static int divider = 0;
static int readCount = 0;
static int delayCount = 0;

static void sump_write_data(uint8_t *buf, int len);
static void sump_writeByte(uint8_t byte);
static void sump_cmd_parser(uint8_t cmdByte);
static void sump_get_metadata();
static void sump_capture_and_send_samples();
static void sump_la_cb(uint8_t *buf, int cnt, int clk, int channel);

// for SUMP pin & cfg definition from menuconfig
static logic_analyzer_config_t la_cfg = {
    .pin = {LA_PIN_0, LA_PIN_1, LA_PIN_2, LA_PIN_3, LA_PIN_4, LA_PIN_5, LA_PIN_6, LA_PIN_7, LA_PIN_8, LA_PIN_9, LA_PIN_10, LA_PIN_11, LA_PIN_12, LA_PIN_13, LA_PIN_14, LA_PIN_15},
    .pin_trigger = LA_PIN_TRIGGER,
    .trigger_edge = LA_PIN_EDGE,
    .number_of_samples = LA_SAMPLE_COUNT,
    .sample_rate = LA_SAMPLE_RATE,
    .number_channels = LA_ANALYZER_CHANNELS,
    .samples_to_psram = LA_ANALYZER_PSRAM,
    .meashure_timeout = LA_DEFAULT_TiMEOUT,
    .logic_analyzer_cb = sump_la_cb};
// hw parametrs
static logic_analyzer_hw_param_t la_hw;

static void sump_capture_and_send_samples()
{
    la_cfg.number_of_samples = readCount;
    la_cfg.sample_rate = PULSEVIEW_MAX_SAMPLE_RATE / (divider + 1);
    if (first_trigger_pin >= 0)
    {
        la_cfg.pin_trigger = la_cfg.pin[first_trigger_pin];
    }
    else
    {
        la_cfg.pin_trigger = -1;
    }

    la_cfg.trigger_edge = first_trigger_val ? GPIO_INTR_POSEDGE : GPIO_INTR_NEGEDGE;
    int err = start_logic_analyzer(&la_cfg);
    if (err)
    {
        return;
    }
}
static void sump_la_cb(uint8_t *buf, int cnt, int clk, int channels)
{
    if (buf == NULL)
    {
        return;
    }
    // sigrok - data send on reverse order
    // psram - burst align - cnt may be less then readCnt -> send zero sample
    int zero_sample = 0;
    int diff = readCount - cnt;
    if (channels == 8)
    {
        uint8_t *bufff = (uint8_t *)buf + readCount - 1 - diff;
        for (int i = 0; i < readCount; i++)
        {
            if (i < diff) // zero sample
            {
                sump_write_data((uint8_t *)(&zero_sample), 1);
            }
            else
            {
                sump_write_data((uint8_t *)(bufff), 1);
                bufff--;
            }
        }
    }
    else if (channels == 16) // 16 channels
    {
        uint16_t *bufff = (uint16_t *)buf + readCount - 1 - diff;
        for (int i = 0; i < readCount; i++)
        {
            if (i < diff) // zero sample
            {
                sump_write_data((uint8_t *)(&zero_sample), 2);
            }
            else
            {
                sump_write_data((uint8_t *)(bufff), 2);
                bufff--;
            }
        }
    }
    else // 4 channels
    {
        uint8_t *bufff = (uint8_t *)buf + (readCount / 2) - 1 - diff;
        for (int i = 0; i < readCount; i++)
        {
            if (i < diff) // zero sample
            {
                sump_write_data((uint8_t *)(&zero_sample), 1);
            }
            else
            {
                if (i & 1)
                {
                    sump_writeByte(*bufff & 0xf);
                    bufff--;
                }
                else
                {
                    sump_writeByte((*bufff >> 4) & 0xf);
                }
            }
        }
    }
}
static void sump_config_uart()
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = SUMP_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = ESP_INTR_FLAG_IRAM;

    ESP_ERROR_CHECK(uart_driver_install(SUMP_UART_PORT_NUM, UART_BUF_SIZE, UART_BUF_SIZE, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(SUMP_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(SUMP_UART_PORT_NUM, SUMP_TEST_TXD, SUMP_TEST_RXD, SUMP_TEST_RTS, SUMP_TEST_CTS));
    ESP_ERROR_CHECK(uart_set_sw_flow_ctrl(SUMP_UART_PORT_NUM, true, 16, 32)); // ??
}
static void sump_getCmd4(uint8_t *cmd)
{
    uart_read_bytes(SUMP_UART_PORT_NUM, cmd, 4, portMAX_DELAY);
}
static uint8_t sump_getCmd()
{
    uint8_t buf;
    uart_read_bytes(SUMP_UART_PORT_NUM, &buf, 1, portMAX_DELAY);
    return buf;
}
static void sump_write_data(uint8_t *buf, int len)
{
    uart_write_bytes(SUMP_UART_PORT_NUM, (const char *)buf, len);
}
static void sump_writeByte(uint8_t byte)
{
    uart_write_bytes(SUMP_UART_PORT_NUM, &byte, 1);
}

// loop read sump command
static void logic_analyzer_sump_task(void *arg)
{
    // read hw parametrs -> remove -> may by on metadata
    la_hw.current_channels = la_cfg.number_channels;
    la_hw.current_psram = la_cfg.samples_to_psram;
    logic_analyzer_get_hw_param(&la_hw);

    sump_config_uart();
    while (1)
    {
        uint8_t cmd = sump_getCmd();
        sump_cmd_parser(cmd);
    }
}
void logic_analyzer_sump(void)
{
    xTaskCreate(logic_analyzer_sump_task, "sump_task", 2048 * 4, NULL, 1, NULL);
}

/*
 *   @brief main sump command loop
 *   @param cmdByte - data byte from uart
 */
static void sump_cmd_parser(uint8_t cmdByte)
{
    static int trigger = 0;
    static int trigger_values = 0;
    union ucmd
    {
        uint32_t u_cmd32;
        uint16_t u_cmd16[2];
        uint8_t u_cmd8[4];
    } cmd;
    switch (cmdByte)
    {
    case SUMP_RESET:
        break;
    case SUMP_QUERY:
        sump_write_data((uint8_t *)"1ALS", 4);
        break;
    case SUMP_ARM:
        sump_capture_and_send_samples();
        break;
    case SUMP_TRIGGER_MASK_CH_A:
        sump_getCmd4(cmd.u_cmd8);
        trigger = cmd.u_cmd32 & 0xffff;
        first_trigger_pin = -1; // trigger not defined
        if (trigger)
        {
            for (int i = 0; i < 16; i++)
                if ((trigger >> i) & 0x1)
                {
                    first_trigger_pin = i; // only one trigger pin
                    break;
                }
        }
        break;
    case SUMP_TRIGGER_VALUES_CH_A:
        sump_getCmd4(cmd.u_cmd8);
        trigger_values = cmd.u_cmd32 & 0xffff;
        first_trigger_val = 0;
        if (trigger)
        {
            first_trigger_val = (trigger_values >> first_trigger_pin) & 1; // 0/1 value trigger
        }
        break;
    case SUMP_TRIGGER_MASK_CH_B:
    case SUMP_TRIGGER_MASK_CH_C:
    case SUMP_TRIGGER_MASK_CH_D:
    case SUMP_TRIGGER_VALUES_CH_B:
    case SUMP_TRIGGER_VALUES_CH_C:
    case SUMP_TRIGGER_VALUES_CH_D:
    case SUMP_TRIGGER_CONFIG_CH_A:
    case SUMP_TRIGGER_CONFIG_CH_B:
    case SUMP_TRIGGER_CONFIG_CH_C:
    case SUMP_TRIGGER_CONFIG_CH_D:
        sump_getCmd4(cmd.u_cmd8);
        break;
    case SUMP_SET_DIVIDER: // divider from freq ????
        sump_getCmd4(cmd.u_cmd8);
        divider = cmd.u_cmd32 & 0xffffff;
        break;
    case SUMP_SET_READ_DELAY_COUNT: // samples or bytes ??????
        sump_getCmd4(cmd.u_cmd8);
        readCount = ((cmd.u_cmd16[0] & 0xffff) + 1) * 4;
        delayCount = ((cmd.u_cmd16[1] & 0xffff) + 1) * 4;
        break;
    case SUMP_SET_BIG_READ_CNT: // samples or bytes ??????
        sump_getCmd4(cmd.u_cmd8);
        readCount = (cmd.u_cmd32 + 1) * 4;
        // delayCount = ((cmd.u_cmd16[1]&0xffff)+1)*4;
        break;

    case SUMP_SET_FLAGS:
        sump_getCmd4(cmd.u_cmd8);
        break;
    case SUMP_GET_METADATA:
        sump_get_metadata();
        break;
    case SUMP_SELF_TEST:
        break;
    default:
        break;
    }
}

static void sump_get_metadata()
{
    // read hw parametrs
    la_hw.current_channels = la_cfg.number_channels;
    la_hw.current_psram = la_cfg.samples_to_psram;
    logic_analyzer_get_hw_param(&la_hw);
    /* device name */
    sump_writeByte((uint8_t)0x01);
    sump_write_data((uint8_t *)"ESP32", 6);
    /* firmware version */
    sump_writeByte((uint8_t)0x02);
    sump_write_data((uint8_t *)"0.00", 5);
    /* sample memory */
    uint32_t capture_size = (la_hw.current_channels > 4) ? (la_hw.max_sample_cnt * (la_hw.current_channels / 8)) : la_hw.max_sample_cnt; // buff size bytes. 4 channels send as 8 channels
    sump_writeByte((uint8_t)0x21);
    sump_writeByte((uint8_t)(capture_size >> 24) & 0xFF);
    sump_writeByte((uint8_t)(capture_size >> 16) & 0xFF);
    sump_writeByte((uint8_t)(capture_size >> 8) & 0xFF);
    sump_writeByte((uint8_t)(capture_size >> 0) & 0xFF);
    /* sample rate defined on HW */
    uint32_t capture_speed = la_hw.max_sample_rate;
    sump_writeByte((uint8_t)0x23);
    sump_writeByte((uint8_t)(capture_speed >> 24) & 0xFF);
    sump_writeByte((uint8_t)(capture_speed >> 16) & 0xFF);
    sump_writeByte((uint8_t)(capture_speed >> 8) & 0xFF);
    sump_writeByte((uint8_t)(capture_speed >> 0) & 0xFF);
    /* number of probes */
    sump_writeByte((uint8_t)0x40);
    sump_writeByte((la_hw.current_channels > 4) ? ((uint8_t)la_hw.current_channels & 0xff) : 8); // 8/16 -> 4 channels send as 8 channels
    /* protocol version (2) */
    sump_writeByte((uint8_t)0x41);
    sump_writeByte((uint8_t)0x02);
    /* end of data */
    sump_writeByte((uint8_t)0x00);
}
