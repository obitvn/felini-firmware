
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
#endif

extern "C"
{

#ifdef CONFIG_IDF_TARGET_ESP32S3
    void app_main(void)
#else
    int main(int argc, char *argv[])
#endif
    {
        lv_porting_init();

        lv_obj_t *label = lv_label_create(lv_scr_act());
        lv_label_set_text(label, "obit tesla!!!!!!");
        lv_obj_center(label);
        HAL::HAL_Init();
        App_Init();

        while (1)
        {
            lv_timer_handler();
            lv_porting_delay();
            #ifdef CONFIG_IDF_TARGET_ESP32S3
                vTaskDelay(10);
            #endif
        }
    }
}