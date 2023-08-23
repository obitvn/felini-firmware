/**
 * @file touch_driver.c
 */

#include "cst816s_touch_driver.h"



void touch_driver_init(void)
{

    cst816_init(CST816_I2C_SLAVE_ADDR);

}


bool is_touched(void)
{

       return cst816_is_touched();

}


void touch_driver_read(lv_indev_drv_t *drv, lv_indev_data_t *data)
{
    bool res = false;

    res = cst816_read(drv, data);


    data->continue_reading = res;

}

