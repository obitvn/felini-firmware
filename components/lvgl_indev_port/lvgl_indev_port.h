#ifndef LVGL_PORT_INDEV_H
#define LVGL_PORT_INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "encoder.h"
#include "cst816s_touch_driver.h"

void lv_port_indev_init(void);
lv_indev_t* get_indev(void);
lv_group_t* get_group(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif