#include "rk816.h"
#include <stdio.h>
#include "esp_log.h"
#include "i2c_manager.h"

#define TAG "RK816"


int rk816_reg_write(uint8_t reg, uint8_t val)
{
	return (int)i2c_manager_write(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &val, 1);
}

int rk816_reg_read(uint8_t reg, uint8_t *val)
{
	// uint8_t buf = 0;
	// i2c_manager_read(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &buf, 1);
	// printf("i2c read reg %x  ", buf);
	// *val = buf;
	// return 1;
	return (int)i2c_manager_read(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &val, 1);
}

uint8_t rk816_bat_read(uint8_t reg)
{
	uint8_t val=0;
	i2c_manager_read(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &val, 1);
	// printf("i2c read reg %x  ", val);
	return val;
}

int rk816_reg_read_return(uint8_t reg, uint8_t *val)
{
	return (int)i2c_manager_read(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &val, 1);
}


int rk816_reg_read_data(uint8_t reg, uint8_t *val, uint16_t size)
{
	return (int)i2c_manager_read(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &val, size);
}

int rk816_reg_write_data(uint8_t reg, uint8_t *val, uint16_t size)
{
	return (int)i2c_manager_write(I2C_NUM_0, RK816_DEFAULT_I2C_ADDRESS, reg, &val, size);
}

void regulator_rk816_set_enable(int channel, bool enable)
{

	uint8_t val = 0;

	switch(channel)
	{
	case 0 ... 3:
		val = (enable ? 0x11 : 0x10) << channel;
		rk816_reg_write(RK816_DCDC_EN_REG1, val);
		break;

	case 4 ... 7:
		val = (enable ? 0x11 : 0x10) << (channel - 4);
		rk816_reg_write(RK816_LDO_EN_REG1, val);
		break;

	case 8 ... 9:
		val = (enable ? 0x11 : 0x10) << (channel - 8);
		rk816_reg_write(RK816_LDO_EN_REG2, val);
		break;

	default:
		break;
	}
}

bool regulator_rk816_get_enable(int channel)
{

	uint8_t val = 0;

	switch(channel)
	{
	case 0 ... 3:
		rk816_reg_read(RK816_DCDC_EN_REG1, &val);
		val = (val >> channel) & 0x1;
		break;

	case 4 ... 7:
		rk816_reg_read(RK816_LDO_EN_REG1, &val);
		val = (val >> (channel - 4)) & 0x1;
		break;

	case 8 ... 9:
		rk816_reg_read(RK816_LDO_EN_REG2, &val);
		val = (val >> (channel - 8)) & 0x1;
		break;

	default:
		break;
	}

	return (val != 0) ? true : false;
}

int  rk816_poll_pwrkey(void) // not working
{
	uint8_t buf=0;
	rk816_reg_read( RK816_INT_STS_REG1, &buf);
	printf("STS reg %x  ", buf);
	/* rising, clear falling */
	if (buf & (1 << 6))
		rk816_reg_write(RK816_INT_STS_REG1, (1 << 5));
	/* falling, clear rising */
	if (buf & (1 << 5))
		rk816_reg_write(RK816_INT_STS_REG1, (1 << 6));

	rk816_reg_read( RK816_INT_STS_REG1, &buf);

	return (buf & (1 << 5));

}


uint8_t rk816_vol_to_reg(int vol, int step, int min, int max)
{
	int reg;

	if(vol < min)
		vol = min;
	else if(vol > max)
		vol = max;

	reg = (vol - min + step - 1) / step;
	return (uint8_t)(reg & 0xff);
}

int rk816_reg_to_vol(uint8_t reg, int step, int min, int max)
{
	int vol = (int)reg * step + min;

	if(vol < min)
		vol = min;
	else if(vol > max)
		vol = max;
	return vol;
}

void regulator_rk816_set_voltage(int channel, int voltage)
{
	uint8_t val;

	switch(channel)
	{
	/* DCDC1 - 0.7125V ~ 1.45V, 0.0125V/step, 2A */
	case 0:
		val = rk816_vol_to_reg(voltage, 12500, 712500, 1450000);
		rk816_reg_write(RK816_BUCK1_ON_VSEL_REG, val);
		break;

	/* DCDC2 - 0.7125V ~ 1.45V, 0.0125V/step, 2A */
	case 1:
		val = rk816_vol_to_reg(voltage, 12500, 712500, 1450000);
		rk816_reg_write(RK816_BUCK2_ON_VSEL_REG, val);
		break;

	/* DCDC3 - 1.0V ~ 1.8V, 1A */
	case 2:
		break;

	/* DCDC4 - 0.8V ~ 3.5V, 0.1V/step, 1A */
	case 3:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3500000);
		rk816_reg_write(RK816_BUCK4_ON_VSEL_REG, val);
		break;

	/* LDO1 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 4:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3400000);
		rk816_reg_write(RK816_LDO1_ON_VSEL_REG, val);
		break;

	/* LDO2 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 5:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3400000);
		rk816_reg_write(RK816_LDO2_ON_VSEL_REG, val);
		break;

	/* LDO3 - 0.8V ~ 3.4V, 0.1V/step, 0.1A */
	case 6:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3400000);
		rk816_reg_write(RK816_LDO3_ON_VSEL_REG, val);
		break;

	/* LDO4 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 7:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3400000);
		rk816_reg_write(RK816_LDO4_ON_VSEL_REG, val);
		break;

	/* LDO5 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 8:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3400000);
		rk816_reg_write(RK816_LDO5_ON_VSEL_REG, val);
		break;

	/* LDO6 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 9:
		val = rk816_vol_to_reg(voltage, 100000, 800000, 3400000);
		rk816_reg_write(RK816_LDO6_ON_VSEL_REG, val);
		break;

	default:
		break;
	}
}

int regulator_rk816_get_voltage(int channel)
{
	int voltage;
	uint8_t val = 0;

	switch(channel)
	{
	/* DCDC1 - 0.7125V ~ 1.45V, 0.0125V/step, 2A */
	case 0:
		rk816_reg_read(RK816_BUCK1_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 12500, 712500, 1450000);
		break;

	/* DCDC2 - 0.7125V ~ 1.45V, 0.0125V/step, 2A */
	case 1:
		rk816_reg_read(RK816_BUCK2_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 12500, 712500, 1450000);
		break;

	/* DCDC3 - 1.0V ~ 1.8V, 1A */
	case 2:
		voltage = 1500000;
		break;

	/* DCDC4 - 0.8V ~ 3.5V, 0.1V/step, 1A */
	case 3:
		rk816_reg_read(RK816_BUCK4_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3500000);
		break;

	/* LDO1 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 4:
		rk816_reg_read(RK816_LDO1_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3400000);
		break;

	/* LDO2 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 5:
		rk816_reg_read(RK816_LDO2_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3400000);
		break;

	/* LDO3 - 0.8V ~ 3.4V, 0.1V/step, 0.1A */
	case 6:
		rk816_reg_read(RK816_LDO3_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3400000);
		break;

	/* LDO4 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 7:
		rk816_reg_read(RK816_LDO4_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3400000);
		break;

	/* LDO5 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 8:
		rk816_reg_read(RK816_LDO5_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3400000);
		break;

	/* LDO6 - 0.8V ~ 3.4V, 0.1V/step, 0.3A */
	case 9:
		rk816_reg_read(RK816_LDO6_ON_VSEL_REG, &val);
		voltage = rk816_reg_to_vol(val, 100000, 800000, 3400000);
		break;

	default:
		voltage = 0;
		break;
	}

	return voltage;
}

void rk816_power_off_shutdown(void)
{
	int ret, i;
	uint8_t reg = 0;

	for (i = 0; i < 10; i++) {
		 ESP_LOGI(TAG,"%s\n", __func__);
		ret = rk816_reg_read(RK816_DEV_CTRL_REG, &reg);
		if (ret < 0) {
			 ESP_LOGI(TAG,
				"rk816 power off try %d times: %d\n", i, ret);
			continue;
		}

		ret = rk816_reg_write(RK816_DEV_CTRL_REG, (reg | (1 << 0)));
		if (ret < 0) {
			 ESP_LOGI(TAG,
				"rk816 power off fail %d times: %d\n", i, ret);
			continue;
		}
	}


	 ESP_LOGE(TAG,"rk816 power off failed!!!\n");

}

unsigned bcd2bin(unsigned char val)
{
	return (val & 0x0f) + (val >> 4) * 10;
}

unsigned char bin2bcd(unsigned val)
{
	return ((val / 10) << 4) + val % 10;
}

bool rk816_rtc_set_time(int second, int minute, int hour, int day, int month, int year, int week)
{

	uint8_t val = 0;

	rk816_reg_read( RK816_RTC_CTRL_REG, &val);
	val |= (0x1 << 0);
	rk816_reg_write( RK816_RTC_CTRL_REG, val);

	rk816_reg_write( RK816_SECONDS_REG, bin2bcd(second));
	rk816_reg_write( RK816_MINUTES_REG, bin2bcd(minute));
	rk816_reg_write( RK816_HOURS_REG, bin2bcd(hour));
	rk816_reg_write( RK816_DAYS_REG, bin2bcd(day));
	rk816_reg_write( RK816_MONTHS_REG, bin2bcd(month));
	rk816_reg_write( RK816_YEARS_REG, bin2bcd(year - 2000));
	rk816_reg_write( RK816_WEEKS_REG, bin2bcd(week));

	rk816_reg_read( RK816_RTC_CTRL_REG, &val);
	val &= ~(0x1 << 0);
	rk816_reg_write( RK816_RTC_CTRL_REG, val);

	return true;
}

bool rk816_rtc_get_time(int *second, int *minute, int *hour, int *day, int *month, int *year, int *week)
{
	uint8_t val = 0;

	val |= (0x1 << 1);
	rk816_reg_write( RK816_RTC_CTRL_REG, val);

	rk816_reg_read( RK816_RTC_CTRL_REG, &val);
	val &= ~(0x1 << 6);
	rk816_reg_write( RK816_RTC_CTRL_REG, val);

	rk816_reg_read( RK816_RTC_CTRL_REG, &val);
	val |= (0x1 << 6) | (0x1 << 7);
	rk816_reg_write( RK816_RTC_CTRL_REG, val);

	rk816_reg_read( RK816_SECONDS_REG, &val);
	*second = bcd2bin(val & 0x7f);
	rk816_reg_read( RK816_MINUTES_REG, &val);
	*minute = bcd2bin(val & 0x7f);
	rk816_reg_read( RK816_HOURS_REG, &val);
	*hour = bcd2bin(val & 0x3f);
	rk816_reg_read( RK816_DAYS_REG, &val);
	*day = bcd2bin(val & 0x3f);
	rk816_reg_read( RK816_MONTHS_REG, &val);
	*month = bcd2bin(val & 0x1f);
	rk816_reg_read( RK816_YEARS_REG, &val);
	*year = bcd2bin(val & 0xff) + 2000;
	rk816_reg_read( RK816_WEEKS_REG, &val);
	*week = bcd2bin(val & 0x07);

	return true;
}


void rk816_init_power(void)
{
	// read version
	uint8_t data[2];
	rk816_reg_read(RK816_CHIP_NAME_REG, &data);
	rk816_reg_read(RK816_CHIP_VER_REG, &data[1]);
	ESP_LOGW(TAG,"rk816 id  0x%x version  0x%x\r\n",  data[0] << 4 | ((data[1] >> 4) & 0xf), data[1] & 0xf);

	int chanel[11];
	
	for(int i=0; i<10; i++)
	{
		chanel[i] =regulator_rk816_get_voltage(i);
	}


	rk816_reg_write( RK816_VB_MON_REG, 0b00000100); //  System low voltage threshold
	rk816_reg_write( RK816_VB_UV_REG_THERMAL_REG, 0b11011000); //  System low voltage threshold
	rk816_reg_write( RK816_PWRON_LP_INT_TIME_REG, 0b00000000); // long press PWRON 2s
	rk816_reg_write( RK816_PWRON_DB_REG, 0b00000000); // : PWRON key de-bounce time 40mS
	// rk816_reg_write( RK816_DEV_CTRL_REG, 0b01001001); // : DEVICE CONTROL REGISTER

	printf("power on source %x\r\n", rk816_bat_read(RK816_ON_SOURCE_REG));
	


	
	ESP_LOGI(TAG,"dcdc1 %d, dcdc2 %d, dcdc3 %d,\r\n dcdc4 %d, ldo1 %d, ldo2 %d,\r\n ldo3 %d, ldo4 %d, ldo5 %d, ldo6 %d\r\n", 
	chanel[1], chanel[2], chanel[3], chanel[4],
	chanel[5], chanel[6], chanel[7], chanel[8],
	chanel[9], chanel[10]);

	regulator_rk816_set_voltage(RK816_LDO1, 3300000);
	regulator_rk816_set_voltage(RK816_LDO2, 3300000);
	regulator_rk816_set_voltage(RK816_LDO3, 3300000);
	regulator_rk816_set_voltage(RK816_LDO4, 3300000);

	

	regulator_rk816_set_enable(RK816_LDO1, true);
	regulator_rk816_set_enable(RK816_LDO2, true);
	regulator_rk816_set_enable(RK816_LDO3, true);
	regulator_rk816_set_enable(RK816_LDO4, true);
}

