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



TaskHandle_t interval_time_task_handle = NULL;
TaskHandle_t frequency_count_task_handle = NULL;

uint32_t freq = 0;

extern "C"
{


    static void interval_time_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "Create IntervalTime task...................");

        frequency_init();
        
        while (1)
        {
                    
            freq = frequency_hz();
            printf("frequency %ld Hz\r\n", freq);
            vTaskDelay(10);
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
    info->frequency = freq;
    info->cmd = CMD_UPDATE;
    info->time = 0;
}

void HAL::IntervalTime_Deinit()
{
    if (interval_time_task_handle != NULL)
    {
        vTaskDelete(interval_time_task_handle);
    }
    frequency_deinit();
}