#include "axp173.h"
// #include "lvgl_i2c/i2c_manager.h"
#include "driver/gpio.h"
#include <string.h>
#include "esp_err.h"
#include "esp_log.h"

// #include <esp_log.h>
#include "i2c_manager.h"

#define TAG "axp"

#define AXP_GET_REG(x)  (x >> 8)
#define AXP_GET_BITNUM(x)   (x & 0xff)

#define AXP_CHECK_VOLT(volt, min, max, ret)   if(volt < min || volt > max){           \
                                                    ESP_LOGI(TAG, "Invalid voltage!");  \
                                                    return ret;                         \
                                                }                                       

#define AXP_READ_STATUS(info, t, bit_num)    info = ((t & (1<<bit_num))? 1 : 0)

// #define AXP_GENERATE_BYTE()

esp_err_t axp_read_byte(uint16_t reg, uint8_t *data){
    return i2c_manager_read(I2C_NUM_0, AXP173_I2C_SLAVE_ADDR, reg | I2C_REG_16, data, 1);
}

esp_err_t axp_read_bytes(uint8_t reg, uint8_t *data, size_t len){
    return i2c_manager_read(I2C_NUM_0, AXP173_I2C_SLAVE_ADDR, reg | I2C_REG_16, data, len);
}

esp_err_t axp_write_byte(uint16_t reg, const uint8_t data){
    return i2c_manager_write(I2C_NUM_0, AXP173_I2C_SLAVE_ADDR, reg | I2C_REG_16, &data, 1);
}



esp_err_t axp_init() {
    ESP_LOGI(TAG, "Init axp173 ...");

    /* Power output control */
    axp_write_byte(0x12, axp_op_generate_byte(true, true, true, true, true, true));

    // axp_en_ctrl(EN_OP_DC2, true);
    axp_en_ctrl(EN_OP_DC1, true);
    axp_en_ctrl(EN_OP_LDO2, true);
    axp_en_ctrl(EN_OP_LDO3, true);
    axp_en_ctrl(EN_OP_LDO4, true);

    axp_en_ctrl(EN_COLUMB, true);
    axp_en_ctrl(EN_ADC_INTER_TEMP, true);


    /* set voltage */
    axp_set_volt(DC1_SET_VOLT, 3300);
    // axp_set_volt(DC1_SET_VOLT, 2275);
    axp_set_volt(LDO2_SET_VOLT, 3300);
    axp_set_volt(LDO3_SET_VOLT, 3300);
    axp_set_volt(LDO4_SET_VOLT, 3300);

    /* PEK Button parameter setting */
    axp_pek_setting(1,1,0);

    axp_info_t info;
    // memset(&info, -1, sizeof(axp_info_t));
    axp_read_info(&info);
    axp_show_info(&info);

    ESP_LOGI(TAG, "Init axp173 done!!!!.");
    return ESP_OK;
}

esp_err_t axp_en_ctrl(en_command_t command, bool enable) {
    esp_err_t ret = ESP_OK;
    uint8_t reg = AXP_GET_REG(command);
    uint8_t bit_num = AXP_GET_BITNUM(command);
    uint8_t tmp;

    ret = axp_read_byte(reg, &tmp);
    if(enable){
        tmp |= (1<<bit_num);    // set bit
    }else{
        tmp &= ~(1<<bit_num);   // clear bit
    }
    ret = axp_write_byte(reg, tmp);

    return ret;
}

esp_err_t axp_set_volt(volt_setting_t channel, int volt) {
    esp_err_t ret = ESP_OK;
    uint8_t reg = AXP_GET_REG(channel);
    uint8_t tmp = 0;

    switch (channel)
    {
    case DC2_SET_VOLT:
        AXP_CHECK_VOLT(volt, 700, 2275, ESP_FAIL);
        tmp = (volt-700)/25;
        ret = axp_write_byte(reg, tmp);
        break;

    case DC1_SET_VOLT:
        AXP_CHECK_VOLT(volt, 700, 3500, ESP_FAIL);
        tmp = (volt-700)/25;
        ret = axp_write_byte(reg, tmp);
        break;

    case LDO4_SET_VOLT:
        AXP_CHECK_VOLT(volt, 700, 3500, ESP_FAIL);
        tmp = (volt-700)/25;
        ret = axp_write_byte(reg, tmp);
        break;

    case LDO2_SET_VOLT:
        AXP_CHECK_VOLT(volt, 1800, 3300, ESP_FAIL);
        ret = axp_read_byte(reg, &tmp);
        tmp &= ~(0b11110000);
        tmp |= ((volt-1800)/100 << 4);
        ret = axp_write_byte(reg, tmp);
        break;
    
    case LDO3_SET_VOLT:
        AXP_CHECK_VOLT(volt, 1800, 3300, ESP_FAIL);
        ret = axp_read_byte(reg, &tmp);
        tmp &= ~(0b00001111);
        tmp |= ((volt-1800)/100);
        ret = axp_write_byte(reg, tmp);
        break;

    case VHOLD_SET_VOLT:
        AXP_CHECK_VOLT(volt, 4000, 4700, ESP_FAIL);
        ret = axp_read_byte(reg, &tmp);
        tmp &= ~(0b00111000);           // Clear the bit field to be written
        tmp |= (((volt-4000)/100) << 3);    // setbit write new data
        ret = axp_write_byte(reg, tmp);
        break;

    case VOFF_SET_VOLT:
        AXP_CHECK_VOLT(volt, 2600, 3300, ESP_FAIL);
        ret = axp_read_byte(reg, &tmp);
        tmp &= ~(0b00000111);
        tmp |= ((volt-2600)/100);
        ret = axp_write_byte(reg, tmp);
        break;
    }

    return ret;
}

esp_err_t axp_read_info(axp_info_t *info) {
    ESP_LOGI(TAG, "Reading axp info.");
    uint8_t tmp;
    axp_read_byte(0x00, &tmp);
    ESP_LOGI(TAG, "0x00 tmp: %d", tmp);
    AXP_READ_STATUS(info->acin_exist, tmp, 7);
    AXP_READ_STATUS(info->vbus_exist, tmp, 5);

    AXP_READ_STATUS(info->bat_current_dir, tmp, 2);


    axp_read_byte(0x01, &tmp);
    ESP_LOGI(TAG, "0x01 tmp: %d", tmp);
    AXP_READ_STATUS(info->axp_over_temp, tmp, 7);
    AXP_READ_STATUS(info->charge_idct, tmp, 6);
    AXP_READ_STATUS(info->bat_exist, tmp, 5);


    axp_read_byte(0x12, &tmp);
    ESP_LOGI(TAG, "0x12 tmp: %d", tmp);
    AXP_READ_STATUS(info->exten, tmp, 6);
    AXP_READ_STATUS(info->dcdc2, tmp, 4);
    AXP_READ_STATUS(info->ldo3, tmp, 3);
    AXP_READ_STATUS(info->ldo2, tmp, 2);
    AXP_READ_STATUS(info->ldo4, tmp, 1);
    AXP_READ_STATUS(info->dcdc1, tmp, 0);


    axp_show_info(info);


        float vbus, bat, charge_current, discharge_current, temp, ts, acbus;

        axp_read_adc_data(DATA_ACIN_VOLT, &acbus);
        axp_read_adc_data(DATA_VBUS_VOLT, &vbus);
        axp_read_adc_data(DATA_BAT_VOLT, &bat);
        axp_read_adc_data(DATA_BAT_CHARGE_CURRENT, &charge_current);
        axp_read_adc_data(DATA_BAT_DISCHARGE_CURRENT, &discharge_current);
        axp_read_adc_data(DATA_INTEL_TEMP, &temp);
        axp_read_adc_data(DATA_TS_ADC, &ts);
        ESP_LOGI(TAG, "ACIN volt: %.2f | VBUS volt: %.2f | BAT volt: %.2f | Charge_current: %.2f | Discharge_current: %.2f | temp: %.2f | ts: %.2f\r\n", acbus, vbus, bat, charge_current, discharge_current, temp, ts);

    
    ESP_LOGI(TAG, "End to read axp info.");
    return ESP_OK;
}

esp_err_t axp_read_adc_data(adc_data_t dc, float *buffer){
    esp_err_t ret = ESP_OK;
    uint8_t reg = AXP_GET_REG(dc);
    uint8_t len = (dc & 0xff);
    uint8_t data[len];  // row data
    ESP_ERROR_CHECK(axp_read_bytes(reg, data, len));
    float step;     // sen = step/1000
    switch (dc)
    {
    case DATA_ACIN_VOLT:
        step = 1.7;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    case DATA_ACIN_CURRENT:
        step = 0.625;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    case DATA_VBUS_VOLT:
        step = 1.7;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    case DATA_VBUS_CURRENT:
        step = 0.375;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    case DATA_INTEL_TEMP:
        step = 0.1;
        *buffer = ((((data[0]<<4) + data[1]) * step)/1000)-144.7;
        break;
    case DATA_TS_ADC:
        step = 0.8;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    case DATA_BAT_POWER:
        step = 1.1/2;
        *buffer = (((data[0]<<16) + (data[1]<<8) + data[2]) * step)/1000;
        break;
    case DATA_BAT_VOLT:
        step = 1.1;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    case DATA_BAT_DISCHARGE_CURRENT:
        step = 0.5;
        *buffer = (((data[0]<<5) + data[1]) * step)/1000;
        break;
    case DATA_BAT_CHARGE_CURRENT:
        step = 0.5;
        *buffer = (((data[0]<<5) + data[1]) * step)/1000;
        break;
    case DATA_APS_VOLT:
        step = 1.4;
        *buffer = (((data[0]<<4) + data[1]) * step)/1000;
        break;
    // case DATA_COLUMB_CHARGE:
    // case DATA_COLUMB_DISCHARGE:
        // break;
    }

    return ret;
}

/**
 * @brief PEK Button parameter setting , '{}' is default
 * 
 * @param boot_time         [0]:128ms _ {1}:512ms _ [2]:1s _ [3]:2s
 * @param longpress_time    [0]:1s _ {1}:1.5s _ [2]:2s _ [3]:2.5s
 * @param shutdown_time     [0]:4s _ {1}:6s _ [2]:8s _ [3]:10s
 * @return esp_err_t 
 */
esp_err_t axp_pek_setting(uint8_t boot_time, uint8_t longpress_time, uint8_t shutdown_time) {
    uint8_t tmp;
    tmp = axp_read_byte(AXP173_PEK, &tmp);
    tmp &= ~(0b11110011);
    tmp |= ((boot_time<<6) | (longpress_time<<4) | shutdown_time);

    return axp_write_byte(AXP173_PEK, tmp);
}

/**
 * @brief ADCSample rate setting
 * 
 * @param rate      [0]:25Hz _ [1]:50Hz _ [2]:100Hz _ [3]:200Hz
 * @return esp_err_t 
 */
esp_err_t axp_set_adc_sample_rate(uint8_t rate){
    uint8_t tmp;
    axp_read_byte(0x84, &tmp);
    tmp &= ~(0b11000000);
    tmp |= (rate << 6);
    return axp_write_byte(0x84, tmp);
}

/**
 * @brief TS pin settings, '{}' is default
 * 
 * @param op_current    Output current：      [0]:20uA _ [1]:40uA _ [2]:60uA _ {3}:80uA
 * @param op_way        Current output mode： [0]: Off _ [1]: Output current when charging _ {2}: ADC sampling _ [3]: Always on
 * @param function      Pin function：        [0]:Battery temperature monitoring _ [1]:External independent ADC
 * @return esp_err_t 
 */
esp_err_t axp_ts_setting(uint8_t op_current, uint8_t op_way, uint8_t function){
    uint8_t tmp;
    tmp = axp_read_byte(0x84, &tmp);
    tmp &= ~(0b00110111);
    tmp |= ((op_current << 4 | (function << 2) | op_way));
    
    return axp_write_byte(0x84, tmp);
}


esp_err_t axp_colum_pause(){
    uint8_t tmp;
    axp_read_byte(0xb8, &tmp);
    tmp |= (1<<6);
    return axp_write_byte(0xb8, tmp);
}
esp_err_t axp_colum_clear(){
    uint8_t tmp;
    axp_read_byte(0xb8, &tmp);
    tmp |= (1<<5);
    return axp_write_byte(0xb8, tmp);
}
/* 未测试 */
esp_err_t axp_read_columb_data(float *buffer){
    uint8_t tmp[4];
    uint32_t columb_in, columb_out;
    esp_err_t ret = ESP_OK;
    ret = axp_read_bytes(0xb0, tmp, 4);
    columb_in = (tmp[0]<<24) + (tmp[1]<<16) + (tmp[2]<<8) + tmp[3];
    ret = axp_read_bytes(0xb4, tmp, 4);
    columb_out = (tmp[0]<<24) + (tmp[1]<<16) + (tmp[2]<<8) + tmp[3];
    ESP_LOGI(TAG,"columb in: %lu, out: %lu", columb_in, columb_out);
    *buffer = 32768 * (columb_in - columb_out) / 3600 / 25;
    return ret;
}

void axp_show_info(axp_info_t *info){
    ESP_LOGI(TAG, "========axp173 info=========");
    ESP_LOGI(TAG, "acin_exist: %d\t| vbus_exist: %d\t\t\t| bat_exist: %d",
        info->acin_exist, info->vbus_exist, info->bat_exist);
    ESP_LOGI(TAG, "temp: %s\t| charge_idct: %s\t| bat_current_dir: %s",
        info->axp_over_temp ? "over temp" : "normal",
        info->charge_idct ? "charging" : "discharge",
        info->bat_current_dir ? "in" : "out");

    ESP_LOGI(TAG, "EXTEN: %d\t\t| DCDC1: %d\t\t\t| DCDC2: %d",
        info->exten, info->dcdc1, info->dcdc2);
    ESP_LOGI(TAG, "LDO2: %d\t\t| LDO3: %d\t\t\t| LDO4: %d",
        info->ldo2, info->ldo3, info->ldo4);
}

uint8_t axp_op_generate_byte(bool dc1, bool dc2, bool exten, bool ldo2, bool ldo3, bool ldo4){
    uint8_t ret = 0;
    if(dc1) ret |= (1<<0);
    if(dc2) ret |= (1<<4);
    if(ldo2) ret |= (1<<2);
    if(ldo3) ret |= (1<<3);
    if(ldo4) ret |= (1<<1);
    return ret;
}
