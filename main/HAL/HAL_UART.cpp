/*
*  Copyright (c) 2018 David Antliff
*/

#include <cstdio>
#include "HAL.h"
#include "stdio.h"

#include "string.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include "ringbuffer.h"

ring_buffer_t rxuart_ring_buffer;

#define ECHO_TEST_TXD (3)
#define ECHO_TEST_RXD (2)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM (2)
#define ECHO_UART_BAUD_RATE (115200)
#define ECHO_TASK_STACK_SIZE (8192)

static const char *TAG = "UART TEST";

#define BUF_SIZE (1024)

uint8_t rxdata[BUF_SIZE];
uint32_t rxdata_len;
bool empty_data = true;

static void echo_task(void *arg)
{
    // printf("echo_task task\n");
    /* Configure parameters of an UART driver,
     * communication pins and install the driver */
    uart_config_t uart_config = {
        .baud_rate = ECHO_UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    int intr_alloc_flags = 0;

#if CONFIG_UART_ISR_IN_IRAM
    intr_alloc_flags = ESP_INTR_FLAG_IRAM;
#endif

    ring_buffer_init(&rxuart_ring_buffer);

    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *)malloc(BUF_SIZE);

    while (1)
    {
        // Read data from the UART
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, data, 512, 20 / portTICK_PERIOD_MS);
        if (len)
        {
            data[len + 1] = '\0';
            ring_buffer_queue_arr(&rxuart_ring_buffer, (char *)data, len + 1);
        }
        vTaskDelay(20);
    }
}

static void uart_config(uint32_t baud)
{
    uart_config_t uart_config = {
        .baud_rate = (int)baud,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
}

TaskHandle_t uart_task_handle = NULL;

/* UART*/
void HAL::UART_Init(UART_Info_t *info)
{
    printf("creat uart task\n");
    xTaskCreate(echo_task, "uart_echo_task", ECHO_TASK_STACK_SIZE, NULL, 10, &uart_task_handle);
}

void HAL::UART_Update(UART_Info_t *info)
{
    switch (info->cmd)
    {
        case CMD_RECV:
        {
            uint32_t datalen =  ring_buffer_num_items(&rxuart_ring_buffer);
            ring_buffer_get_peek(&rxuart_ring_buffer, (char *)rxdata, datalen + 1);
            info->receive = (char*)&rxdata;
            info->recv_length = datalen + 1;
            break;
        }
        case CMD_SETUP:
            uart_config(info->baud);
        
        default:
            break;
    }
    
}

void HAL::UART_Deinit()
{
    if (uart_task_handle != NULL)
    {
        vTaskDelete(uart_task_handle);
    }
    uart_driver_delete(ECHO_UART_PORT_NUM);
}