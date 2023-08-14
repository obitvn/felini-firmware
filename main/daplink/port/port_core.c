#include "port_common.h"
#include "ringbuffer.h"
#include "driver/uart.h"
#include "esp_log.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static uint8_t rx_ch;
extern ring_buffer_t uart_ring_buffer;
extern ring_buffer_t cdc_ring_buffer;

void dap_platform_init(void)
{
    /*!< xxx */

    /*!< ringbuffer init */
    ring_buffer_init(&uart_ring_buffer);
    ring_buffer_init(&cdc_ring_buffer);
}

void dap_gpio_init(void)
{
    // gpio_write(LED_CONNECTED, 1U);
    // gpio_write(LED_RUNNING, 1U);
    // gpio_set_mode(LED_CONNECTED, GPIO_OUTPUT_MODE);
    // gpio_set_mode(LED_RUNNING, GPIO_OUTPUT_MODE);
}

void dap_uart_send_from_ringbuff(void)
{
    if (ring_buffer_is_empty(&cdc_ring_buffer))
    {
        return;
    }
    /*!< Send */
    uint16_t len = ring_buffer_num_items(&cdc_ring_buffer);
    char send_buffer[len];
    ring_buffer_dequeue_arr(&cdc_ring_buffer, send_buffer, len);
    /*!< Uart send */
    uart_write_bytes(UART_NUM_1, (const char *)send_buffer, len);
}


static uart_config_t uart_config;

#define BUF_SIZE (1024)
// uint8_t data[BUF_SIZE] = "testabc\r\n";
const int uart_buffer_size = (1024 * 4);
QueueHandle_t uart_queue;

static void rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    int rxBytes = 0;
    size_t buffered_len;
    ESP_LOGI(RX_TASK_TAG, "Read UART task\r\n");

    uint8_t *data = (uint8_t *)malloc(BUF_SIZE + 1);
    while (1)
    {
        uart_get_buffered_data_len(UART_NUM_1, &buffered_len);
        if (buffered_len > 0)
        {
            uart_read_bytes(UART_NUM_1, data, buffered_len, 20 / portTICK_PERIOD_MS); 
            ring_buffer_queue_arr(&uart_ring_buffer, (const char *)data, buffered_len);
            ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);
        }
            vTaskDelay(1);
    }
    free(data);
}


//baudrate 230400, databits 8, parity 0, setup0
//baudrate 921600, databits 5, parity 1, setup2     //databit 5 stop2, parity odd  (none 0, odd 1, even 2, mark 3, space 4)
static TaskHandle_t *uart_task_handle = NULL;

void dap_uart_config(uint32_t baudrate, uint8_t databits, uint8_t parity, uint8_t stopbits)
{
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */

        uart_config.baud_rate = baudrate;
        uart_config.data_bits = databits - 5;
        uart_config.parity = parity;
        uart_config.stop_bits = stopbits;
        uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
        uart_config.source_clk = UART_SCLK_DEFAULT;

         int intr_alloc_flags = 0;
    if(uart_is_driver_installed(UART_NUM_1))
        uart_driver_delete(UART_NUM_1);
        

    // Don't put printf, print log in here, device will crash!!!!!!!!!!!!!!!!!!!!!

    uart_driver_install(UART_NUM_1, uart_buffer_size, uart_buffer_size, 10, NULL, intr_alloc_flags);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, DAP_UART_TX, DAP_UART_RX, -1, -1);

    if(uart_task_handle != NULL)
    {
        vTaskDelete(uart_task_handle);
        uart_task_handle = NULL;
    }
    xTaskCreate(rx_task, "uart_rx_task", 1024 * 8, NULL, 10, uart_task_handle);
}

uint32_t led_connect_val=0;
uint32_t led_runnning_val = 0;

void set_led_connect(uint32_t bit)
{
    led_connect_val = bit;
}

void set_led_running(uint32_t bit)
{
    led_runnning_val = bit;
}

uint32_t get_led_connect(void)
{
    return led_connect_val;
}

uint32_t get_led_running(void)
{
    return led_runnning_val;
}