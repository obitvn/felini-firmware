#include "lv_porting.h"
#include "lvgl.h"

#define MONITOR_HOR_RES 280
#define MONITOR_VER_RES 240
#define MONITOR_BUF_SIZE MONITOR_HOR_RES *MONITOR_VER_RES

#ifdef CONFIG_IDF_TARGET_ESP32S3

#include "lvgl_disp_port.hpp"
#include "lvgl_indev_port.h"


#include "rk816.h"
#include "i2c_manager.h"

int32_t i2c_read(void *handle, uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size)
{
    return i2c_manager_read(I2C_NUM_0, address, reg, buffer, size);
}

int32_t i2c_write(void *handle, uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size)
{
    return i2c_manager_write(I2C_NUM_0, address, reg, buffer, size);
}



void disp_drv_init(void);
void indev_drv_init(void);

static void lv_tick_task(void *arg)
{
    (void) arg;

    lv_tick_inc(1);
}

void lv_porting_init(void)
{
    
    rk816_init_power();

    lv_init();
    esp_register_freertos_tick_hook((void *)lv_tick_task);

    lv_port_disp_init();


    lv_port_indev_init();

    // int sec, min, hour, day, month, year, week;
    // rk816_rtc_get_time(&sec, &min, &hour, &day, &month, &year, &week);
    // printf("get time sec %d, min %d, hour %d, day %d, month %d, year %d, week %d\r\n", sec, min, hour, day, month, year, week);
    
    // rk816_rtc_set_time(12, 45, 14, 21, 8, 2089, 31);

    // vTaskDelay(3000);
    
    // rk816_rtc_get_time(&sec, &min, &hour, &day, &month, &year, &week);
    // printf("get time sec %d, min %d, hour %d, day %d, month %d, year %d, week %d\r\n", sec, min, hour, day, month, year, week);
    // int button=0;
    // while (1)
    // {
    //     button = rk816_poll_pwrkey();
    //     printf("button %d state \r\n", button);
    //     vTaskDelay(200);
    // }
    

}

void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    int a = 0;
}

void disp_drv_init(void)
{
    int a = 0;
}

void indev_read(struct _lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    int a = 0;
}

void indev_drv_init(void)
{
    int a = 0;
}

void lv_porting_delay(void)
{
    // int a = 0;
    vTaskDelay(10);
}

#else

#define _DEFAULT_SOURCE  /* needed for usleep() */
#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" issue*/
#include <SDL2/SDL.h>
#include "sdl/sdl.h"

static int tick_thread(void *data)
{
    LV_UNUSED(data);

    while (1)
    {
        SDL_Delay(5);
        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
    }

    return 0;
}

lv_group_t *group;

void lv_porting_init(void)
{
    lv_init();
    monitor_init();
    // SDL创建线程
    SDL_CreateThread(tick_thread, "tick", NULL);

    // 初始化图像缓冲区, 第二个缓冲区(可选)可以传入NULL
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t buf_1[MONITOR_BUF_SIZE];
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, MONITOR_BUF_SIZE);

    /* 注册显示驱动 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = monitor_flush;
    disp_drv.hor_res = MONITOR_HOR_RES;
    disp_drv.ver_res = MONITOR_VER_RES;
    disp_drv.antialiasing = 1;
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

    /* 注册鼠标驱动 */
    static lv_indev_drv_t indev_drv_1;
    lv_indev_drv_init(&indev_drv_1);
    indev_drv_1.type = LV_INDEV_TYPE_POINTER;
    indev_drv_1.read_cb = sdl_mouse_read;
    lv_indev_t *mouse_indev = lv_indev_drv_register(&indev_drv_1);

    static lv_indev_drv_t indev_drv_2;
    lv_indev_drv_init(&indev_drv_2);
    indev_drv_2.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_2.read_cb = sdl_mousewheel_read;
    lv_indev_t *mousewheel_indev = lv_indev_drv_register(&indev_drv_2);

    
    group = lv_group_create();
    lv_indev_set_group(mousewheel_indev, group);
    lv_group_set_default(group);
}

void inline lv_porting_delay(void)
{
    SDL_Delay(5);
}

#endif
