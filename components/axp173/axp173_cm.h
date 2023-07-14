#ifndef _AXP173_CM_H_
#define _AXP173_CM_H_

#ifdef __cplusplus
extern "C" {
#endif

// [12]reg [3] [4]bit_num
typedef enum {
    EN_OP_EXTEN = 0x1002,
    EN_OP_DC2   = 0x1000,
    EN_OP_LDO3  = 0x1203,
    EN_OP_LDO2  = 0x1202,
    EN_OP_LDO4  = 0x1201,
    EN_OP_DC1   = 0x1200,

    EN_VHOLD_LIMIT = 0x3006,    // VBUS VHOLD 限压控制, 1->限压,0->不限压
    EN_VBUS_CURRENT_LIMIT = 0x3001, // VBUS 限流控制使能信号, 0:关闭,1:打开
    EN_CHARGE   = 0x3307,   // 1->charge, 0->discharge

    /* ADC ENABLE1 */
    EN_ADC_BAT_VOLT = 0x8207,
    EN_ADC_BAT_CURRENT = 0x8206,
    EN_ADC_ACIN_VOLT = 0x8205,
    EN_ADC_ACIN_CURRENT = 0x8204,
    EN_ADC_VBUS_VOLT = 0x8203,
    EN_ADC_VBUS_CURRENT = 0x8202,
    EN_ADC_APS_VOLT = 0x8201,
    EN_ADC_TS_PIN = 0x8200,
    EN_ADC_INTER_TEMP = 0x8307,

    /* colum */
    EN_COLUMB    = 0xb807,
}en_command_t;

// [12]reg [3]bit_num [4]bit_length
typedef enum {
    DC2_SET_VOLT    = 0x2305,   // 700~2275, 25mV/step
    DC1_SET_VOLT    = 0x2606,   // 700~3500, 25mV/step
    LDO4_SET_VOLT   = 0x2706,   // 700~3500, 25mV/step
    LDO2_SET_VOLT   = 0x2844,   // 1800~3300, 100mV/step   
    LDO3_SET_VOLT   = 0x2804,   // 1800~3300, 100mV/step
    VHOLD_SET_VOLT  = 0x3033,   // 4000~4700, 100mV/step
    VOFF_SET_VOLT   = 0x3103,   // 2600~3300, 100mV/step
}volt_setting_t;    


// [12]reg [3] [4]data_length, eg:0x5602 reg=0x56 占 2 byte
typedef enum {
    DATA_ACIN_VOLT = 0x5602,
    DATA_ACIN_CURRENT = 0x5802,
    DATA_VBUS_VOLT = 0x5a02,
    DATA_VBUS_CURRENT = 0x5c02,
    DATA_INTEL_TEMP = 0x5e02,
    DATA_TS_ADC = 0x6202,

    DATA_BAT_POWER = 0x7003,
    DATA_BAT_VOLT = 0x7802,
    DATA_BAT_CHARGE_CURRENT = 0x7a02,
    DATA_BAT_DISCHARGE_CURRENT = 0x7c02,
    
    DATA_APS_VOLT = 0x7e02,

    // DATA_COLUMB_CHARGE = 0xb004,
    // DATA_COLUMB_DISCHARGE = 0xb404,
}adc_data_t;

#ifdef __cplusplus
}
#endif

#endif
