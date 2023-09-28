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
#include "esp_etm.h"
#include "esp_private/periph_ctrl.h"
#include "esp_private/etm_interface.h"

static const char *TAG = "intervalTime";

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your board spec ////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define MES_FREG_GPIO 2

#define EXAMPLE_GPTIMER_RESOLUTION_HZ 1000000 // 1MHz, 1 tick = 1us

TaskHandle_t interval_time_task_handle = NULL;



uint32_t tof_ticks;
extern "C"
{

    static void interval_time_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "Create IntervalTime task...................");

        while (1)
        {
            vTaskDelay(pdMS_TO_TICKS(500));
        }
    }
}


/* IntervalTime*/
void HAL::IntervalTime_Init()
{
    xTaskCreate(interval_time_task, "interval_time_task", 1024, NULL, 10, &interval_time_task_handle);
}
void HAL::IntervalTime_GetInfo(IntervalTime_Info_t *info)
{

}

void HAL::IntervalTime_Deinit()
{
    if (interval_time_task_handle != NULL)
    {
        vTaskDelete(interval_time_task_handle);
    }
}