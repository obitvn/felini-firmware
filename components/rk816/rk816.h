 /* This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 */

#ifndef RK816_H__
#define RK816_H__

/// si5351 i2c 0x60
//  


#include "stdbool.h"

#define RK816_DEFAULT_I2C_ADDRESS   0x1a    

#define RK816_DCDC1                 0x00
#define RK816_DCDC2                 0x01
#define RK816_DCDC3                 0x02
#define RK816_DCDC4                 0x03
#define RK816_LDO1                  0x04
#define RK816_LDO2                  0x05
#define RK816_LDO3                  0x06
#define RK816_LDO4                  0x07
#define RK816_LDO5                  0x08
#define RK816_LDO6                  0x09


// HEX ADDRESS      FUNCTION      DESCRIPTION    R/W DEFAULT
// RTC REGISTER
#define RK816_SECONDS_REG 		    0x00 //RW 0x00
#define RK816_MINUTES_REG 		    0x01 //RW 0x50
#define RK816_HOURS_REG 		    0x02 //RW 0x08
#define RK816_DAYS_REG 		        0x03 //RW 0x21
#define RK816_MONTHS_REG 		    0x04 //RW 0x01
#define RK816_YEARS_REG 		    0x05 //RW 0x15
#define RK816_WEEKS_REG 		    0x06 //RW 0x03
#define RK816_ALARM_SECONDS_REG 	0x08 //RW 0x00
#define RK816_ALARM_MINUTES_REG 	0x09 //RW 0x00
#define RK816_ALARM_HOURS_REG 		0x0A //RW 0x00
#define RK816_ALARM_DAYS_REG 		0x0B //RW 0x01
#define RK816_ALARM_MONTHS_REG 		0x0C //RW 0x01
#define RK816_ALARM_YEARS_REG 		0x0D //RW 0x00
#define RK816_RTC_CTRL_REG 		    0x10 //RW 0x00
#define RK816_RTC_STATUS_REG 		0x11 //RW 0x82
#define RK816_RTC_INT_REG 		    0x12 //RW 0x00
#define RK816_RTC_COMP_LSB_REG 		0x13 //RW 0x00
#define RK816_RTC_COMP_MSB_REG 		0x14 //RW 0x00
#define RK816_CLK32KOUT_REG 		0x20 //RW 0x01
// VERSION REGISTER
#define RK816_CHIP_NAME_REG 		0x17 //RO 0x81
#define RK816_CHIP_VER_REG 		    0x18 //RO 0x61
#define RK816_OTP_VER_REG 		    0x19 //RO 0000/otp<3:0>
// POWER ON/OFF REGISTER
#define RK816_VB_MON_REG 		    0x21 //RW 0x14
#define RK816_VB_UV_REG_THERMAL_REG 0x22 //RW 0x00
#define RK816_PWRON_LP_INT_TIME_REG 0x47 //RW 0x20
#define RK816_PWRON_DB_REG 		    0x48 //RW 0x40
#define RK816_DEV_CTRL_REG 		    0x4B //RW 0x00
#define RK816_ON_SOURCE_REG 		0xAE //RO 0x00
#define RK816_OFF_SOURCE_REG 		0xAF //RO 0x00
// POWER CHANNELS ENABLE REGISTER
#define RK816_DCDC_EN_REG1 		    0x23 //RW Boot0:0x0F Boot1:0000/otp<3:0>
#define RK816_DCDC_EN_REG2 		    0x24 //RW Boot0:0x00 Boot1:00000/otp<1:0> /0
#define RK816_SLP_DCDC_EN_REG 		0x25 //RW Boot0:0x0F Boot1:0/otp<6:0>
#define RK816_SLP_LDO_EN_REG 		0x26 //RW Boot0:0x36 Boot1:00/otp<5:0>
#define RK816_LDO_EN_REG1 		    0x27 //RW Boot0:0x06 Boot1:0000/otp<3:0>
#define RK816_LDO_EN_REG2 		    0x28 //RW Boot0:0x03 Boot1:0000/otp<3:0>
// BUCK AND LDO CONFIG REGISTER
#define RK816_BUCK1_CONFIG_REG 		0x2E //RW 0x7A
#define RK816_BUCK1_ON_VSEL_REG 	0x2F //RW Boot0:0x1F Boot1:00/otp<5:0>
#define RK816_BUCK1_SLP_VSEL_REG 	0x30 //RW Boot0:0x1F Boot1:00/otp<5:0>
#define RK816_BUCK2_CONFIG_REG 		0x32 //RW 0x7A
#define RK816_BUCK2_ON_VSEL_REG 	0x33 //RW Boot0:0x1F Boot1:00/otp<5:0>
#define RK816_BUCK2_SLP_VSEL_REG 	0x34 //RW Boot0:0x1F Boot1:00/otp<5:0>
#define RK816_BUCK3_CONFIG_REG 		0x36 //RW 0x2A
#define RK816_BUCK4_CONFIG_REG 		0x37 //RW 0x2A
#define RK816_BUCK4_ON_VSEL_REG 	0x38 //RW Boot0:0x19 Boot1:000/otp<4:0>
#define RK816_BUCK4_SLP_VSEL_REG 	0x39 //RW Boot0:0x19 Boot1:000/otp<4:0>
#define RK816_LDO1_ON_VSEL_REG 		0x3B //RW Boot0:0x22 Boot1:001/otp<4:0>
#define RK816_LDO1_SLP_VSEL_REG 	0x3C //RW Boot0:0x02 Boot1:000/otp<4:0>
#define RK816_LDO2_ON_VSEL_REG 		0x3D //RW Boot0:0x2A Boot1:001/otp<4:0>
#define RK816_LDO2_SLP_VSEL_REG 	0x3E //RW Boot0:0x0A Boot1:000/otp<4:0>
#define RK816_LDO3_ON_VSEL_REG 		0x3F //RW Boot0:0x23 Boot1:001/otp<4:0>
#define RK816_LDO3_SLP_VSEL_REG 	0x40 //RW Boot0:0x03 Boot1:000/otp<4:0>
#define RK816_LDO4_ON_VSEL_REG 		0x41 //RW Boot0:0x22 Boot1:001/otp<4:0>
#define RK816_LDO4_SLP_VSEL_REG 	0x42 //RW Boot0:0x02 Boot1:000/otp<4:0>
#define RK816_LDO5_ON_VSEL_REG 		0x43 //RW Boot0:0x36 Boot1:001/otp<4:0>
#define RK816_LDO5_SLP_VSEL_REG 	0x44 //RW Boot0:0x16 Boot1:000/otp<4:0>
#define RK816_LDO6_ON_VSEL_REG 		0x45 //RW Boot0:0x36 Boot1:001/otp<4:0>
#define RK816_LDO6_SLP_VSEL_REG 	0x46 //RW Boot0:0x16 Boot1:000/otp<4:0>
// INTERRUPT REGISTER
#define RK816_INT_STS_REG1 		    0x49 //RW 0x00
#define RK816_INT_STS_MSK_REG1 		0x4A //RW 0x00
#define RK816_INT_STS_REG2 		    0x4C //RW 0x00
#define RK816_INT_STS_MSK_REG2 		0x4D //RW 0x00
#define RK816_INT_STS_REG3 		    0x4E //RW 0x00
#define RK816_INT_STS_MSK_REG3 		0x4F //RW 0x00
#define RK816_GPIO_IO_POL_REG 		0x50 //RW 0x26
// CHARGER, BOOST AND OTG REGISTER
#define RK816_OTG_BUCK_LDO_CONFIG_REG 0x2A //RW 00000/otp<0>/00
#define RK816_CHRG_CONFIG_REG 		0x2B //RW 0x3A
#define RK816_BOOST_CON_REG 		0x54 //RW 0x00
#define RK816_BOOST_ON_VSEL_REG 	0x54 //RW 0x73
#define RK816_BOOST_SLP_VSEL_REG 	0x55 //RW 0x60
#define RK816_CHRG_BOOST_CONFIG_REG 0x9A //RW 0xC0
#define RK816_SUP_STS_REG 		    0xA0 //RW 0x0C
#define RK816_USB_CTRL_REG 		    0xA1 //RW 01000/otp<2:0>
#define RK816_CHRG_CTRL_REG1 		0xA3 //RW 0xB3
#define RK816_CHRG_CTRL_REG2 		0xA4 //RW 0x52
#define RK816_CHRG_CTRL_REG3 		0xA5 //RW 0x82
#define RK816_BAT_CTRL_REG 		    0xA6 //RW 0xC3
#define RK816_BAT_HTS_TS_REG 		0xA8 //RW 0x00
#define RK816_BAT_LTS_TS_REG 		0xA9 //RW 0xFF
// ADC AND FUEL GAUGE REGISTER
#define RK816_TS_CTRL_REG 		    0xAC //RW 0x83
#define RK816_ADC_CTRL_REG 		    0xAD //RW 0x30
#define RK816_GGCON_REG 		    0xB0 //RW 0x4A
#define RK816_GGSTS_REG 		    0xB1 //RW 0x40
#define RK816_ZERO_CUR_ADC_REGH 	0xB2 //RW 0x00
#define RK816_ZERO_CUR_ADC_REGL 	0xB3 //RW 0x00
#define RK816_GASCNT_CAL_REG3 		0xB4 //RW 0x00
#define RK816_GASCNT_CAL_REG2 		0xB5 //RW 0x00
#define RK816_GASCNT_CAL_REG1 		0xB6 //RW 0x00
#define RK816_GASCNT_CAL_REG0		0xB7 //RW 0x00
#define RK816_GASCNT_REG3 		    0xB8 //RO 0x00
#define RK816_GASCNT_REG2 		    0xB9 //RO 0x00
#define RK816_GASCNT_REG1 		    0xBA //RO 0x00
#define RK816_GASCNT_REG0 		    0xBB //RO 0x00
#define RK816_BAT_CUR_REGH 		    0xBC //RO 0x00
#define RK816_BAT_CUR_REGL 		    0xBD //RO 0x00
#define RK816_TS_ADC_REGH 		    0xBE //RO 0x00
#define RK816_TS_ADC_REGL 		    0xBF //RO 0x00
#define RK816_USB_ADC_REGH 		    0xC0 //RO 0x00
#define RK816_USB_ADC_REGL 		    0xC1 //RO 0x00
#define RK816_BAT_OCV_REGH 		    0xC2 //RO 0x00
#define RK816_BAT_OCV_REGL 		    0xC3 //RO 0x00
#define RK816_BAT_VOL_REGH 		    0xC4 //RO 0x00
#define RK816_BAT_VOL_REGL 		    0xC5 //RO 0x00
#define RK816_RELAX_ENTRY_THRES_REGH 	0xC6 //RW 0x00
#define RK816_RELAX_ENTRY_THRES_REGL 	0xC7 //RW 0x60
#define RK816_RELAX_EXIT_THRES_REGH 	0xC8 //RW 0x00
#define RK816_RELAX_EXIT_THRES_REGL 	0xC9 //RW 0x60
#define RK816_RELAX_VOL1_REGH 		0xCA //RO 0x00
#define RK816_RELAX_VOL1_REGL 		0xCB //RO 0x00
#define RK816_RELAX_VOL2_REGH 		0xCC //RO 0x00
#define RK816_RELAX_VOL2_REGL 		0xCD //RO 0x00
#define RK816_RELAX_CUR1_REGH 		0xCE //RO 0x00
#define RK816_RELAX_CUR1_REGL 		0xCF //RO 0x00
#define RK816_RELAX_CUR2_REGH 		0xD0 //RO 0x00
#define RK816_RELAX_CUR2_REGL 		0xD1 //RO 0x00
#define RK816_CAL_OFFSET_REGH 		0xD2 //RW 0x7F
#define RK816_CAL_OFFSET_REGL 		0xD3 //RW 0xFF
#define RK816_NON_ACT_TIMER_CNT_REG 0xD4 //RO 0x00
#define RK816_VCALIB0_REGH 		    0xD5 //RO 0x00
#define RK816_VCALIB0_REGL 		    0xD6 //RO 0x00
#define RK816_VCALIB1_REGH 		    0xD7 //RO 0x00
#define RK816_VCALIB1_REGL 		    0xD8 //RO 0x00
#define RK816_FCC_GASCNT_REG3 		0xD9 //RO 0x00
#define RK816_FCC_GASCNT_REG2 		0xDA //RO 0x00
#define RK816_FCC_GASCNT_REG1 		0xDB //RO 0x00
#define RK816_FCC_GASCNT_REG0 		0xDC //RO 0x00
#define RK816_IOFFSET_REGH 		    0xDD //RO 0x00
#define RK816_IOFFSET_REGL 		    0xDE //RO 0x00
#define RK816_SLEEP_CON_SAMP_CUR_REG 0xDF //RW 0x60
// DATA REGISTER
#define RK816_DATA0_REG 		    0xE0 //RW 0x00
#define RK816_DATA1_REG 		    0xE1 //RW 0x00
#define RK816_DATA2_REG 		    0xE2 //RW 0x00
#define RK816_DATA3_REG 		    0xE3 //RW 0x00
#define RK816_DATA4_REG 		    0xE4 //RW 0x00
#define RK816_DATA5_REG 		    0xE5 //RW 0x00
#define RK816_DATA6_REG 		    0xE6 //RW 0x00
#define RK816_DATA7_REG 		    0xE7 //RW 0x00
#define RK816_DATA8_REG 		    0xE8 //RW 0x00
#define RK816_DATA9_REG 		    0xE9 //RW 0x00
#define RK816_DATA10_REG 		    0xEA //RW 0x00
#define RK816_DATA11_REG 		    0xEB //RW 0x00
#define RK816_DATA12_REG 		    0xEC //RW 0x00
#define RK816_DATA13_REG 		    0xED //RW 0x00
#define RK816_DATA14_REG 		    0xEE //RW 0x00
#define RK816_DATA15_REG 		    0xEF //RW 0x00
#define RK816_DATA16_REG 		    0xF0 //RW 0x00
#define RK816_DATA17_REG 		    0xF1 //RW 0x00
#define RK816_DATA18_REG 		    0xF2 //RW 0x00
// RK816 Datasheet Rev 1.3
// Copyright ©2017 Fuzhou Rockchip Electronics Co., Ltd. 
//


void rk816_init_power(void);

int  rk816_poll_pwrkey(void);
void rk816_power_off_shutdown(void);
bool regulator_rk816_get_enable(int channel);
void regulator_rk816_set_enable(int channel, bool enable);
void regulator_rk816_set_voltage(int channel, int voltage);
int regulator_rk816_get_voltage(int channel);

bool rk816_rtc_get_time(int *second, int *minute, int *hour, int *day, int *month, int *year, int *week);
bool rk816_rtc_set_time(int second, int minute, int hour, int day, int month, int year, int week);

#endif
