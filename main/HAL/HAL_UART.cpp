/*
*  Copyright (c) 2018 David Antliff
*/

#include <cstdio>
#include "HAL.h"
#include "stdio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

#define ECHO_TEST_TXD (3)
#define ECHO_TEST_RXD (2)
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM (2)
#define ECHO_UART_BAUD_RATE (115200)
#define ECHO_TASK_STACK_SIZE (8192)

static const char *TAG = "UART TEST";

#define BUF_SIZE (2048)

uint8_t rxdata[1024];
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

    ESP_ERROR_CHECK(uart_driver_install(ECHO_UART_PORT_NUM, BUF_SIZE * 2, 0, 0, NULL, intr_alloc_flags));
    ESP_ERROR_CHECK(uart_param_config(ECHO_UART_PORT_NUM, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(ECHO_UART_PORT_NUM, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS));

    // Configure a temporary buffer for the incoming data
    

    while (1)
    {
        // Read data from the UART
        int len = uart_read_bytes(ECHO_UART_PORT_NUM, rxdata, (BUF_SIZE - 1), 20 / portTICK_PERIOD_MS);
        if (len)
        {
            rxdata[len] = '\0';
            rxdata_len = len + 1;
            empty_data = false;
            ESP_LOGI(TAG, "Recv str: %s", (char *)rxdata);
        }
        vTaskDelay(150);
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
            if (!empty_data)
            {
                info->recv_length = rxdata_len;
                info->receive =  (char*)&rxdata;
            }
            break;
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