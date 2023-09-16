#include <cstdio>
#include "HAL.h"
#include "stdio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include <driver/i2c.h>

#define IIC_SDA_PIN 18
#define IIC_SCL_PIN 21

static const char *TAG = "i2cscanner";


void HAL::IIC_Init()
{
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = IIC_SDA_PIN;
    conf.scl_io_num = IIC_SCL_PIN;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    i2c_param_config(I2C_NUM_1, &conf);
    i2c_driver_install(I2C_NUM_1, I2C_MODE_MASTER, 0, 0, 0);
}

void HAL::IIC_Scan(IIC_Info_t *info)
{

}


void HAL::IIC_GetInfo(IIC_Info_t *info)
{

}

void HAL::IIC_Deinit()
{
    i2c_driver_delete(I2C_NUM_1);
}