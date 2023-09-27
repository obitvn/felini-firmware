
#include <cstdlib>
#include <thread>
#include <iostream>

#include "porting/lv_porting.h"
#include "lvgl.h"

#include "App/App.h"
#include "HAL/HAL.h"

#ifdef CONFIG_IDF_TARGET_ESP32S3
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_freertos_hooks.h"
    #include "freertos/semphr.h"
    #include "esp_system.h"
    #include "driver/gpio.h"
    #include "driver/uart.h"
    #include "axp173.h"
    #include "dap_main.h"
    #include "esp_log.h"
    #define TAG "main"


#endif



extern "C"
{

#ifdef CONFIG_IDF_TARGET_ESP32S3
    static SemaphoreHandle_t lvgl_mutex = NULL;
    void app_main(void)
    {
        lvgl_mutex = xSemaphoreCreateMutex();
#else
    int main(int argc, char *argv[])
    {
#endif
    
        lv_porting_init();
        HAL::HAL_Init();
        App_Init();
        while (1)
        {

#ifdef CONFIG_IDF_TARGET_ESP32S3
            if(pdTRUE == xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
            {
#endif
            lv_task_handler();
            lv_porting_delay();
#ifdef CONFIG_IDF_TARGET_ESP32S3
            xSemaphoreGive(lvgl_mutex);
            }
#endif
        }
    }
}