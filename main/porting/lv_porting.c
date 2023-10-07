#include "lv_porting.h"
#include "lvgl.h"

#define MONITOR_HOR_RES 280
#define MONITOR_VER_RES 240
#define MONITOR_BUF_SIZE MONITOR_HOR_RES *MONITOR_VER_RES

#ifdef CONFIG_IDF_TARGET_ESP32S3

#include "lvgl_disp_port.hpp"
#include "lvgl_indev_port.h"


#include "axp192.h"
#include "i2c_manager.h"

int32_t i2c_read(void *handle, uint8_t address, uint8_t reg, uint8_t *buffer, uint16_t size)
{
    return i2c_manager_read(I2C_NUM_0, address, reg, buffer, size);
}

int32_t i2c_write(void *handle, uint8_t address, uint8_t reg, const uint8_t *buffer, uint16_t size)
{
    return i2c_manager_write(I2C_NUM_0, address, reg, buffer, size);
}

axp192_t axp;



void disp_drv_init(void);
void indev_drv_init(void);

static void lv_tick_task(void *arg)
{
    (void) arg;

    lv_tick_inc(1);
}

void lv_porting_init(void)
{
    /* Add pointers to the glue functions. */
    axp.read = &i2c_read;
    axp.write = &i2c_write;

    /* You could set the handle here. It can be pointer to anything. */
    axp.handle = NULL;

    axp192_init(&axp);

    /* Be careful when setting voltages not to brick your board. */
    axp192_ioctl(&axp, AXP192_DCDC1_SET_VOLTAGE, 0);
    axp192_ioctl(&axp, AXP192_DCDC2_SET_VOLTAGE, 0);
    axp192_ioctl(&axp, AXP192_DCDC3_SET_VOLTAGE, 3300);
    axp192_ioctl(&axp, AXP192_LDOIO0_SET_VOLTAGE, 0);
    axp192_ioctl(&axp, AXP192_LDO2_SET_VOLTAGE, 3300);
    axp192_ioctl(&axp, AXP192_LDO3_SET_VOLTAGE, 3300);

    axp192_ioctl(&axp, AXP192_SHUTDOWN_VOLTAGE, 3100);

    axp192_ioctl(&axp, AXP192_DCDC1_DISABLE);
    axp192_ioctl(&axp, AXP192_DCDC2_DISABLE);
    axp192_ioctl(&axp, AXP192_DCDC3_ENABLE);
    axp192_ioctl(&axp, AXP192_LDOIO0_DISABLE);
    axp192_ioctl(&axp, AXP192_LDO2_ENABLE);
    axp192_ioctl(&axp, AXP192_LDO3_ENABLE);
    axp192_ioctl(&axp, AXP192_EXTEN_DISABLE);

    axp192_ioctl(&axp, AXP192_COULOMB_COUNTER_ENABLE);


    // for(int i=0; i<10; i++)
    // {
    //     float vacin, iacin, vvbus, ivbus, temp, pbat, vts, vbat, icharge, idischarge, vaps, cbat;

    //     /* All ADC registers will be read as floats. */
    //     axp192_read(&axp, AXP192_ACIN_VOLTAGE, &vacin);
    //     axp192_read(&axp, AXP192_ACIN_CURRENT, &iacin);
    //     axp192_read(&axp, AXP192_LDO23_VOLTAGE, &vvbus);
    //     axp192_read(&axp, AXP192_VBUS_CURRENT, &ivbus);
    //     axp192_read(&axp, AXP192_TEMP, &temp);
    //     axp192_read(&axp, AXP192_TS_INPUT, &vts);
    //     axp192_read(&axp, AXP192_BATTERY_POWER, &pbat);
    //     axp192_read(&axp, AXP192_BATTERY_VOLTAGE, &vbat);
    //     axp192_read(&axp, AXP192_CHARGE_CURRENT, &icharge);
    //     axp192_read(&axp, AXP192_DISCHARGE_CURRENT, &idischarge);
    //     axp192_read(&axp, AXP192_APS_VOLTAGE, &vaps);
    //     axp192_read(&axp, AXP192_COULOMB_COUNTER, &cbat);

    //     printf(
    //         "vacin: %.2fV iacin: %.2fA vvbus: %.2fV ivbus: %.2fA vts: %.2fV temp: %.0fC "
    //         "pbat: %.2fmW vbat: %.2fV icharge: %.2fA idischarge: %.2fA, vaps: %.2fV cbat: %.2fmAh\r\n",
    //         vacin, iacin, vvbus, ivbus, vts, temp, pbat, vbat, icharge, idischarge, vaps, cbat);

    //     vTaskDelay(200);
    // }


    lv_init();
    esp_register_freertos_tick_hook((void *)lv_tick_task);

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
