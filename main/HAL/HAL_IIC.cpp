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

#define IIC_SDA_PIN 3
#define IIC_SCL_PIN 2

static const char *TAG = "i2cscanner";

// https://learn.adafruit.com/i2c-addresses/the-list

void HAL::IIC_Init()
{
    printf("IIC_Init()\n");
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
{       esp_err_t res;
        i2c_cmd_handle_t cmd = i2c_cmd_link_create();
        i2c_master_start(cmd);
        i2c_master_write_byte(cmd, (info->addr << 1) | I2C_MASTER_WRITE, 1 /* expect ack */);
        i2c_master_stop(cmd);

        printf("finđing %d\n", info->addr); 

        res = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10 / portTICK_PERIOD_MS);
        if (res == 0)
        {
            info->status = 1;
            printf("match\n");
        }
        else
            info->status = 0;
        i2c_cmd_link_delete(cmd);
}


void HAL::IIC_GetInfo(IIC_Info_t *info)
{

}

void HAL::IIC_Deinit()
{
        printf("IIC_DeInit()\n");
        i2c_driver_delete(I2C_NUM_1);
}