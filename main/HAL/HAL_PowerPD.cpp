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
        gpio_set_level((gpio_num_t)45, 0);

        // PD_UFP.init(PD_POWER_OPTION_MAX_20V);
        PD_UFP.init_PPS(PPS_V(5), PPS_A(2.0), PD_POWER_OPTION_MAX_POWER);
        while (1)
        {
            /* code */
            PD_UFP.run();
            // if (PD_UFP.get_voltage() >= PD_V(5.0) && PD_UFP.get_current() >= PD_A(1.5))
            // {
            //     ESP_LOGI(TAG, "volt %d, current %d\n", PD_UFP.get_voltage() * 50, PD_UFP.get_current() * 10);
            //     PD_UFP.get_power_info(NULL);
            // }
            vTaskDelay(5);
        }
        }
}

void HAL::PowerPD_Init()
{
    ESP_LOGI(TAG, "power_pd_c init \r\n");
    xTaskCreate(usb_pd_task, "usb_pd_task", 1024 * 8, NULL, 10, &usb_pd_task_handle);
}

void HAL::PowerPD_Deinit()
{
    
    ESP_LOGI(TAG, "endtask \r\n");
    if (usb_pd_task_handle != NULL)
    {
        vTaskDelete(usb_pd_task_handle);
    }
    PD_UFP.stop();
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
    if (PD_UFP.is_PPS_ready())
        pd_info->pd_stt = STATUS_POWER_PPS;
    else if (PD_UFP.is_power_ready())
        pd_info->pd_stt = STATUS_POWER_TYP;
    else
        pd_info->pd_stt = STATUS_POWER_NA;

    pd_info->get_voltage = PD_UFP.get_voltage();
    pd_info->get_current = PD_UFP.get_current(); 
}

void HAL::PowerPD_Config(PowerPD_Info_t *pd_info)
{
    printf("config %d v %d A \n", pd_info->set_voltage / 1000, pd_info->set_current / 1000);
    PD_UFP.set_PPS(PPS_V(pd_info->set_voltage/1000), PPS_A(pd_info->set_current/1000));
}

void HAL::PowerPD_GetInfo(PowerPD_Info_t *info)
{

}
