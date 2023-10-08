/*
* Copyright © 2022 Band Industries Inc.
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software 
* without restriction, including without limitation the rights to use, copy, modify, merge, 
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons 
* to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or 
* substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR 
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE 
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, 
* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
* SOFTWARE.
*/

#include <esp_log.h>

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include <lvgl.h>
#else
#include <lvgl/lvgl.h>
#endif

#include "cst816s.h"
#include "i2c_manager.h"
#include "driver/gpio.h"

#define TOUCH_HORIZONTAL_X 280
#define TOUCH_VERTICAL_Y   240

#define TAG "CST816"

cst816_status_t cst816_status;

//[BJ] TODO: Below functions are ADF specific, if I am to contribute to main repo this needs to be resolved!
static esp_err_t _cst816_i2c_read(uint8_t slave_addr, uint8_t register_addr, uint8_t *data_buf, uint8_t len) {
    return i2c_manager_read(I2C_NUM_0, slave_addr, register_addr, data_buf, len);
}

static esp_err_t _cst816_i2c_write8(uint8_t slave_addr, uint8_t register_addr, uint8_t data) {
    uint8_t buffer = data;
    return i2c_manager_write(I2C_NUM_0, slave_addr, register_addr, &buffer, 1);
}

uint8_t cst816t_read_len(uint16_t reg_addr,uint8_t *data,uint8_t len)
{
    uint8_t res=0;
    res = i2c_manager_read(I2C_NUM_0, CST816_I2C_SLAVE_ADDR, reg_addr, data, len);

    return res;
}


/**
  * @brief  Initialize for cst816 communication via I2C
  * @param  dev_addr: Device address on communication Bus (I2C slave address of cst816).
  * @retval None
  */
void cst816_init(uint8_t dev_addr) {
     if (!cst816_status.inited) 
     {
        cst816_status.i2c_dev_addr = dev_addr;
        uint8_t version;
        uint8_t versionInfo[3];
        esp_err_t ret;

        //Initialize non-IIC GPIOs
        gpio_set_direction(CST816_TOUCH_RST_PIN, GPIO_MODE_OUTPUT);
        gpio_set_pull_mode(CST816_TOUCH_RST_PIN, GPIO_PULLUP_ONLY);

        //Reset and wake cst816
        gpio_set_level(CST816_TOUCH_RST_PIN, 0);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(CST816_TOUCH_RST_PIN, 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);


        ESP_LOGI(TAG, "Initializing cst816 0x%x", dev_addr);
        int i = 0;
        if ((ret = _cst816_i2c_read(dev_addr, 0x15, &version, 1) != ESP_OK))
        {
            ESP_LOGE(TAG, "Error reading version from device: %s",
            esp_err_to_name(ret));    // Only show error the first time
        }
        if ((ret = _cst816_i2c_read(dev_addr, 0xA7, versionInfo, 3) != ESP_OK))
        {
            ESP_LOGE(TAG, "Error reading versionInfo from device: %s",
            esp_err_to_name(ret));    // Only show error the first time
        }
        ESP_LOGI(TAG, "CST816 version %d, versionInfo: %d.%d.%d", version, versionInfo[0], versionInfo[1], versionInfo[2]);
        cst816_status.inited = true;
    }
}

/**
  * @brief  Get the touch screen X and Y positions values. Ignores multi touch
  * @param  drv:
  * @param  data: Store data here
  * @retval Always false
  */
#define SWAPXY 0
#define INVERTX 0
#define INVERTY 0

bool cst816_is_touched(void)
{
    uint8_t touch_val = 1;
    cst816t_read_len( 0x02, &touch_val, 1);
    return touch_val ? true : false;
}

bool cst816_read(lv_indev_drv_t *drv, lv_indev_data_t *data) {

    uint8_t data_raw[8];
    cst816t_read_len( 0x01, data_raw, 6);

    uint8_t gestureID = data_raw[0];
    uint8_t points = data_raw[1];
    uint8_t event = data_raw[2] >> 6;
    uint16_t point_x = 0;
    uint16_t point_y = 0;

    // point_x = (data_raw[3] | ((data_raw[2] & 0x0F) << 8));
    // point_y = (data_raw[5] | ((data_raw[4] & 0x0F) << 8));

    point_x = ((data_raw[2] & 0xF) << 8) + data_raw[3];
    point_y = ((data_raw[4] & 0xF) << 8) + data_raw[5];

    int temp;
    temp = point_y;
    point_y = point_x;
    point_x = temp;
    point_y = TOUCH_VERTICAL_Y - point_y;
    
    if (points > 0){
        data->state = LV_INDEV_STATE_PR;
    }
    else{
        data->state = LV_INDEV_STATE_REL;
    }
    
    if(point_x > TOUCH_HORIZONTAL_X) 
        data->point.x = 0;
    else data->point.x = point_x;

    if(point_x < 0 ) point_x = 0;
    if(point_y < 0 ) point_y = 0;


    if(point_y > TOUCH_VERTICAL_Y) 
        data->point.y = 0;
    else data->point.y = point_y;

    // NONE = 0x00,
    // SWIPE_UP = 0x01,
    // SWIPE_DOWN = 0x02,
    // SWIPE_LEFT = 0x03,
    // SWIPE_RIGHT = 0x04,
    // SINGLE_CLICK = 0x05,
    // DOUBLE_CLICK = 0x0B, 11
    // LONG_PRESS = 0x0C, 12

    if(gestureID == 0x04)
    {
        data->key = LV_KEY_UP;
    }
    else if (gestureID == 0x03)
    {
        data->key = LV_KEY_DOWN;
    }
    else if (gestureID == 0x02)
    {
        data->key = LV_KEY_LEFT;
    }
    else if (gestureID == 0x01)
    {
        data->key = LV_KEY_RIGHT;
    }
    else if (gestureID == 0x0c)
    {
        data->key = LV_KEY_HOME;
    }

    // printf("%u,%u\n",data->point.x, data->point.y);

    return false;
}