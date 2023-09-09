/*
 * INA226 - TI Current/Voltage/Power Monitor Code
 * Copyright (C) 2021 Craig Peacock
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <stdio.h>
#include <string.h>
#include "i2c_manager.h"
#include "driver/gpio.h"
#include "ina226.h"

/*Porting*/
esp_err_t i2c_write_byte(uint8_t address, uint8_t command, uint8_t data)
{
 return i2c_manager_write(I2C_NUM_0, address, command, &data, 1);
}

esp_err_t i2c_write_short(uint8_t address, uint8_t command, uint16_t data)
{
 return i2c_manager_write(I2C_NUM_0, address, command, &data, sizeof(data));
}

esp_err_t i2c_write_buf(uint8_t address, uint8_t command, uint8_t *data, uint8_t len)
{
 return i2c_manager_write(I2C_NUM_0, address, command, data, len);
}

uint8_t i2c_read_byte(uint8_t address, uint8_t command)
{
 uint8_t val=0;
 i2c_manager_read(I2C_NUM_0, address, command, &val, 1);
 return val;
}

uint16_t i2c_read_short(uint8_t address, uint8_t command)
{
 uint16_t val=0;
 i2c_manager_read(I2C_NUM_0, address, command, &val, 2);
 return val;
}
  
esp_err_t i2c_read_buf( uint8_t address, uint8_t command, uint8_t *buffer, uint8_t len)
{
 return i2c_manager_read(I2C_NUM_0, address, command, buffer, len);
}

/*INA layer*/


void ina226_init()
{
	i2c_write_short(INA226_SLAVE_ADDRESS, INA226_CFG_REG, 0x8000);	// Reset
	i2c_write_short(INA226_SLAVE_ADDRESS, INA226_CFG_REG, 0x4527);	// Average over 16 Samples

	float current_LSB = 5 / 32768.0;

	uint16_t calVal = 0.00512 / (current_LSB * INA226_SHUNT_VALUE);
	// currentDivider_mA = 0.001 / current_LSB;
	// pwrMultiplier_mW = 1000.0 * 25.0 * current_LSB;

	i2c_write_short(INA226_SLAVE_ADDRESS, INA226_CAL_REG, calVal); // 1A, 0.100Ohm Resistor

	printf("Manufacturer ID:  0x%04X\r\n",i2c_read_short(INA226_SLAVE_ADDRESS, INA226_MANUFACTURER_ID));
	printf("Die ID Register:  0x%04X\r\n",i2c_read_short(INA226_SLAVE_ADDRESS, INA226_DIE_ID));
	printf("Configuration Register: 0x%04X\r\n",i2c_read_short(INA226_SLAVE_ADDRESS, INA226_CFG_REG));
}

float ina226_voltage(  )
{
	unsigned int iBusVoltage;
	float fBusVoltage;

	iBusVoltage = i2c_read_short(INA226_SLAVE_ADDRESS, INA226_BUS_VOLT_REG);
	fBusVoltage = (iBusVoltage) * 0.00125;
	printf("Bus Voltage = %.2fV, ", fBusVoltage);

	return (fBusVoltage);
}

float ina226_current(  )
{
	unsigned int iCurrent;
	float fCurrent;

	iCurrent = i2c_read_short(INA226_SLAVE_ADDRESS, INA226_CURRENT_REG);
	// Internally Calculated as Current = ((ShuntVoltage * CalibrationRegister) / 2048)
	fCurrent = iCurrent * 0.0005;
	printf("Current = %.3fA\r\n", fCurrent);

	return (fCurrent);
}

float ina226_power(  )
{
	unsigned int iPower;
	float fPower;

	iPower = i2c_read_short(INA226_SLAVE_ADDRESS, INA226_POWER_REG);
	// The Power Register LSB is internally programmed to equal 25 times the programmed value of the Current_LSB
	fPower = iPower * 0.0125;

	printf("Power = %.2fW\r\n", fPower);
	return (fPower);
}

