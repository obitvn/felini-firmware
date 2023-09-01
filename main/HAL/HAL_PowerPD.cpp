#include <cstdio>
#include "HAL.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "PD_UFP.h"

#define TAG "PD HAL"
class PD_UFP_c PD_UFP;

TaskHandle_t usb_pd_task_handle;

extern "C"
{

    static void usb_pd_task(void *pvParameter)
    {
        ESP_LOGI(TAG, "power_pd_c task on \r\n");
        gpio_set_direction((gpio_num_t)45, GPIO_MODE_OUTPUT);
        gpio_set_level((gpio_num_t)45, 1);

        PD_UFP.init(PD_POWER_OPTION_MAX_20V);
        while (1)
        {
            /* code */
            PD_UFP.run();
            if (PD_UFP.get_voltage() >= PD_V(5.0) && PD_UFP.get_current() >= PD_A(1.5))
            {
                ESP_LOGI(TAG, "volt %d, current %d\n", PD_UFP.get_voltage() * 50, PD_UFP.get_current() * 10);
            }
            vTaskDelay(5);
        }
        
    }
}

void HAL::PowerPD_Init()
{
    ESP_LOGI(TAG, "power_pd_c init \r\n");
    // if (usb_pd_task_handle != NULL)
    // {
    //     vTaskDelete(usb_pd_task_handle);
    //     usb_pd_task_handle = NULL;
    // }
    xTaskCreate(usb_pd_task, "usb_pd_task", 1024 * 2, NULL, 10, &usb_pd_task_handle);
}

void HAL::PowerPD_Deinit()
{
    
    ESP_LOGI(TAG, "endtask \r\n");
    if (usb_pd_task_handle != NULL)
    {
        vTaskDelete(usb_pd_task_handle);
        // usb_pd_task_handle = NULL;
    }
    PD_UFP.stop();
    // usb_pd_task_handle = NULL;
}

void HAL::PowerPD_PowerOn()
{
    gpio_set_level((gpio_num_t)45, 1);
}

void HAL::PowerPD_PowerOff()
{
    gpio_set_level((gpio_num_t)45, 0);
}

void HAL::PowerPD_Update(PowerPD_Info_t *pd_info)
{
    
}

void HAL::PowerPD_Config(PowerPD_Info_t *pd_info)
{
    
    switch (pd_info->pd_type)
    {
    case PD_PDO_TYPE_FIXED_SUPPLY:
        PD_UFP.init(PD_POWER_OPTION_MAX_20V);
        break;
    case PD_PDO_TYPE_VARIABLE_SUPPLY: 
        PD_UFP.set_PPS(pd_info->set_voltage, pd_info->set_current);
        break;

        default:
        break;
    }
}

void HAL::PowerPD_GetInfo(PowerPD_Info_t *info)
{

}
