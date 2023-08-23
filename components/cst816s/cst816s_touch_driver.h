/**
 * @file touch_driver.h
 */

#ifndef CST816S_TOUCH_DRIVER_H__
#define CST816S_TOUCH_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include <stdint.h>
#include <stdbool.h>

#include "cst816s.h"
#include "lvgl.h"

/*********************
*      DEFINES
*********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void touch_driver_init(void);


void touch_driver_read(lv_indev_drv_t *drv, lv_indev_data_t *data);


bool is_touched(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* CST816S_TOUCH_DRIVER_H__ */

