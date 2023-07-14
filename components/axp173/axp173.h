#ifndef _AXP173_H_
#define _AXP173_H_


#include "lvgl_i2c/i2c_manager.h"
#include "driver/gpio.h"
#include "axp173_cm.h"
#include "axp173_reg.h"



#ifdef __cplusplus
extern "C" {
#endif





/* ↓ custom define */
#define AXP173_I2C_SLAVE_ADDR   0x34
#define AXP173_PIN_IRQ          39 

/* ↑ custom define */

// 基本只会存01的值
typedef struct{
    /* REG 00H: 输入电源状态 */
    uint32_t acin_exist : 1;
    uint32_t vbus_exist : 1;
    uint32_t bat_current_dir : 1;   // 0:电池在放电；1:电池被充电

    /* REG 01H: 电源工作模式以及充电状态指示 */
    uint32_t axp_over_temp : 1;     // 0:未过温； 1:过温
    uint32_t charge_idct : 1;       // 0:未充电或充电已完成； 1:正在充电
    uint32_t bat_exist : 1;         // 0:无电池连接； 1:电池已连接

    /* REG 12H: 电源输出控制 */
    uint32_t exten : 1;         // 0:关闭； 1:打开
    uint32_t dcdc2 : 1;
    uint32_t ldo3 : 1;
    uint32_t ldo2 : 1;
    uint32_t ldo4 : 1;
    uint32_t dcdc1 : 1;
}axp_info_t;


/* ================================================================= */

esp_err_t axp_init();
esp_err_t axp_en_ctrl(en_command_t command, bool enable);
esp_err_t axp_set_volt(volt_setting_t channel, int volt);
esp_err_t axp_read_info(axp_info_t *info);

// about adc
esp_err_t axp_set_adc_sample_rate(uint8_t rate);
esp_err_t axp_read_adc_data(adc_data_t dc, float *buffer);


esp_err_t axp_pek_setting(uint8_t boot_time, uint8_t longpress_time, uint8_t shutdown_time);
esp_err_t axp_ts_setting(uint8_t op_current, uint8_t op_way, uint8_t function);

esp_err_t axp_colum_pause();
esp_err_t axp_colum_clear();
esp_err_t axp_read_columb_data(float *buffer);

// tools
void axp_show_info(axp_info_t *info);
uint8_t axp_op_generate_byte(bool dc1, bool dc2, bool exten, bool ldo2, bool ldo3, bool ldo4);

#ifdef __cplusplus
}
#endif

#endif
