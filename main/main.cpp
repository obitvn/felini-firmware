
#include <cstdlib>
#include <thread>
#include <iostream>

#include "porting/lv_porting.h"
#include "lvgl.h"

#include "App/App.h"
#include "HAL/HAL.h"

extern "C"
{

#ifdef ESP32S3_BUILD
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
        }
    }
}