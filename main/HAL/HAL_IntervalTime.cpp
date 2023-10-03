/*
*  Copyright (c) 2018 David Antliff
*/

#include <cstdio>
#include "HAL.h"
#include "stdio.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_etm.h"
#include "driver/gpio_etm.h"
#include "driver/gptimer.h"
#include "driver/gptimer_etm.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "soc/soc_caps.h"
#include "soc/periph_defs.h"
#include "esp_log.h"
#include "esp_check.h"
#include "esp_heap_caps.h"


static const char *TAG = "intervalTime";

#include "frequency_count.h"

#define CONFIG_FREQ_SIGNAL_GPIO         5
#define CONFIG_SAMPLING_WINDOW_GPIO     17

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your board spec ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define GPIO_SIGNAL_INPUT (CONFIG_FREQ_SIGNAL_GPIO)
#define GPIO_RMT_GATE (CONFIG_SAMPLING_WINDOW_GPIO)


// internal signals for GPIO constant levels
#define GPIO_CONSTANT_LOW 0x30
#define GPIO_CONSTANT_HIGH 0x38

#define PCNT_UNIT (0)
#define PCNT_CHANNEL (PCNT_CHANNEL_0)
#define RMT_CHANNEL (RMT_CHANNEL_0)
#define RMT_MAX_BLOCKS (2) // allow up to 2 * 64 * (2 * 32767) RMT periods in window
#define RMT_CLK_DIV 160    // results in 2us steps (80MHz / 160 = 0.5 MHz
// #define RMT_CLK_DIV       20    // results in 0.25us steps (80MHz / 20 = 4 MHz
// #define RMT_CLK_DIV       1     // results in 25ns steps (80MHz / 2 / 1 = 40 MHz)

#define SAMPLE_PERIOD 12.0 // seconds

// The counter is signed 16-bit, so maximum positive value is 32767
// The filter is unsigned 10-bit, maximum value is 1023. Use full period of maximum frequency.
// For higher expected frequencies, the sample period and filter must be reduced.

// suitable up to 16,383.5 Hz
#define WINDOW_DURATION 10.0 // seconds
#define FILTER_LENGTH 1023   // APB @ 80MHz, limits to < 39,100 Hz

    // suitable up to 163,835 Hz
    // #define WINDOW_LENGTH 0.1  // seconds
    // #define FILTER_LENGTH 122  // APB @ 80MHz, limits to < 655,738 Hz

    // suitable up to 1,638,350 Hz
    // #define WINDOW_LENGTH 0.01  // seconds
    // #define FILTER_LENGTH 12  // APB @ 80MHz, limits to < 3,333,333 Hz

    // suitable up to 16,383,500 Hz - no filter
    // #define WINDOW_LENGTH 0.001  // seconds
    // #define FILTER_LENGTH 0  // APB @ 80MHz, limits to < 40 MHz

TaskHandle_t interval_time_task_handle = NULL;
TaskHandle_t frequency_count_task_handle = NULL;

extern "C"
{


    static void interval_time_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "Create IntervalTime task...................");

        // frequency_init();
        uint32_t freq=0;
        while (1)
        {
            // freq = frequency_hz();
            printf("frequency %ld Hz\r\n", freq);
            vTaskDelay(100);
        }
        
    }
}


/* IntervalTime*/
void HAL::IntervalTime_Init()
{
    xTaskCreate(interval_time_task, "interval_time_task", 1024*8, NULL, 10, &interval_time_task_handle);
}
void HAL::IntervalTime_GetInfo(IntervalTime_Info_t *info)
{

}

void HAL::IntervalTime_Deinit()
{
    if (interval_time_task_handle != NULL)
    {
        vTaskDelete(frequency_count_task_handle);
        vTaskDelete(interval_time_task_handle);
    }
}