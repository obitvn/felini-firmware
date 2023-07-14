#ifndef _AXP173_REG_H_
#define _AXP173_REG_H_


#ifdef __cplusplus
extern "C" {
#endif
/* registers */
#define AXP173_POWER_STATUS     (0x00)
#define AXP173_CHARGE_STATUS    (0x01)
// #define AXP173_OTG_VBUS_STATUS  (0x04)


#define AXP173_EXTEN_DC2_SW     (0x10)  //EXTEN & DC-DC2 开关控制寄存器
#define AXP173_DC1_LDO234_SW    (0x12)  //DC-DC1/LDO4 & LDO2/3 开关控制寄存器

/* 输出电压设置 */
#define AXP173_DC2_VOLT         (0x23)  //DC-DC2 输出电压设置
#define AXP173_DC2_VOLT_SLOPE   (0x25)  //DC-DC2 动态电压调节参数设置

#define AXP173_DC1_VOLT         (0x26)  //DC-DC1 输出电压设置
#define AXP173_LDO4_VOLT        (0x27)  //LDO4 输出电压设置
#define AXP173_LDO23_VOLT       (0x28)  //LDO2/3 输出电压设置


#define AXP173_VBUS_TO_IPSOUT   (0x30)  //VBUS-IPSOUT 通路设置寄存器
#define AXP173_SHUTDOWN_VOLT    (0x31)  //VOFF 关机电压设置寄存器
#define AXP173_SHUTDOWN_BAT_CHGLED  (0x32)  //关机、电池检测、CHGLED 控制寄存器

#define AXP173_CHARGE_CONTROL_1 (0x33)  //充电控制寄存器 1
#define AXP173_CHARGE_CONTROL_2 (0x34)  //充电控制寄存器 2

#define AXP173_PEK              (0x36)  //PEK 参数设置寄存器
// #define AXP173_DCDC_FREQUENCY   (0x37)  //DCDC 转换器工作频率设置寄存器
// #define AXP173_BAT_CHG_L_TEMP   (0x38)  //电池充电低温报警设置寄存器
// #define AXP173_BAT_CHG_H_TEMP   (0x39)  //电池充电高温报警设置寄存器

// #define AXP173_APS_LOW_POWER1   (0x3a)  //APS 低电 Level1 设置寄存器
// #define AXP173_APS_LOW_POWER2   (0x3b)  //APS 低电 Level2 设置寄存器
// #define AXP173_BAT_DISCHG_L_TEMP    (0x3c)  //电池放电低温报警设置寄存器
// #define AXP173_BAT_DISCHG_H_TEMP    (0x3d)  //电池放电高温报警设置寄存器


#define AXP173_DCDC_MODE        (0x80)  //DCDC 工作模式设置寄存器
#define AXP173_ADC_ENABLE_1     (0x82)  //ADC 使能设置寄存器 1
#define AXP173_ADC_ENABLE_2     (0x83)  //ADC 使能设置寄存器 2
#define AXP173_ADC_RATE_TS_PIN  (0x84)  //ADC 采样率设置，TS pin 控制寄存器


// #define AXP173_TIMER_CONTROL            (0x8a)  //定时器控制寄存器
// #define AXP173_VBUS_MONITOR             (0x8b)  //VBUS 监测设置寄存器
// #define AXP173_TEMP_SHUTDOWN_CONTROL    (0x8f)  //过温关机控制寄存器


/* Interrupt control registers */
#define AXP173_IRQ_EN_CONTROL_1 (0x40)  //IRQ 使能控制寄存器 1
#define AXP173_IRQ_EN_CONTROL_2 (0x41)  //IRQ 使能控制寄存器 2
#define AXP173_IRQ_EN_CONTROL_3 (0x42)  //IRQ 使能控制寄存器 3
#define AXP173_IRQ_EN_CONTROL_4 (0x43)  //IRQ 使能控制寄存器 4

#define AXP173_IRQ_STATUS_1     (0x44)  //IRQ 状态寄存器 1
#define AXP173_IRQ_STATUS_2     (0x45)  //IRQ 状态寄存器 2
#define AXP173_IRQ_STATUS_3     (0x46)  //IRQ 状态寄存器 3
#define AXP173_IRQ_STATUS_4     (0x47)  //IRQ 状态寄存器 4


/* ADC data registers */
#define AXP173_ACIN_VOLTAGE     (0x56)  //ACIN 电压 ADC 数据高 8 位, 低4位在 (0x57)
#define AXP173_ACIN_CURRENT     (0x58)  //ACIN 电流 ADC 数据高 8 位, 低4位在 (0x59)
#define AXP173_VBUS_VOLTAGE     (0x5a)  //VBUS 电压 ADC 数据高 8 位, 低4位在 (0x5b)
#define AXP173_VBUS_CURRENT     (0x5c)  //VBUS 电流 ADC 数据高 8 位, 低4位在 (0x5d)

//温度相关
#define AXP173_TEMP             (0x5e)  //AXP173 内部温度监测 ADC 数据高 8 位, 低4位在 (0x5f)
#define AXP173_TS_INPUT         (0x62)  //TS 输入 ADC 数据高 8 位，默认监测电池温度,, 低4位在 (0x63)


#define AXP173_BAT_POWER                (0x70)  //电池瞬时功率高 8 位，中 8 位(0x71)， 高 8 位(0x72) 
#define AXP173_BAT_VOLTAGE              (0x78)  //电池电压高 8 位，低 4 位(0x79)
#define AXP173_CHARGE_CURREN            (0x7a)  //电池充电电流高 8 位, 低 5 位(0x7b)
#define AXP173_DISCHARGE_CURRENT        (0x7c)  //电池放电电流高 8 位, 低 5 位(0x7d)
#define AXP173_APS_VOLTAGE              (0x7e)  //APS 电压高 8 位, 低 4 位(0x7f)
#define AXP173_CHARGE_COULOMB           (0xb0)  //电池充电库仑计数据寄存器 3,2(0xb1),1(0xb2),0(0xb3)
#define AXP173_DISCHARGE_COULOMB        (0xb4)  //电池放电库仑计数据寄存器 3,2(0xb5),1(0xb6),0(oxb7)
#define AXP173_COULOMB_COUNTER_CONTROL  (0xb8)  //库仑计控制寄存器

/* Computed ADC */
#define AXP173_COULOMB_COUNTER          (0xff)

#ifdef __cplusplus
}
#endif

#endif

