#include "lv_porting.h"
#include "lvgl.h"

#define MONITOR_HOR_RES 280
#define MONITOR_VER_RES 240
#define MONITOR_BUF_SIZE MONITOR_HOR_RES *MONITOR_VER_RES

#ifdef CONFIG_IDF_TARGET_ESP32S3

#include "lvgl_disp_port.h"
#include "lvgl_indev_port.h"

void disp_drv_init(void);
void indev_drv_init(void);

void lv_porting_init(void)
{
    // static void *lv_buf = NULL;
    // lv_buf = heap_caps_malloc(240*280*2, MALLOC_CAP_DMA);
    // assert(lv_buf != NULL);
    // printf("start up ++++++++++++++++++++++++++++++++++++++");
    lv_init();
    // heap_caps_free(lv_buf);
    lv_port_disp_init();


    lv_port_indev_init();
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

void inline lv_porting_delay(void)
{
    int a = 0;
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
}

void inline lv_porting_delay(void)
{
    SDL_Delay(5);
}

#endif
