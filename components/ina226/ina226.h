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

#ifndef MAIN_INA226_H_
#define MAIN_INA226_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define INA226_SLAVE_ADDRESS	0x40
#define INA226_CFG_REG		0x00
#define INA226_SHUNT_VOLT_REG	0x01
#define INA226_BUS_VOLT_REG	0x02
#define INA226_POWER_REG	0x03
#define INA226_CURRENT_REG	0x04
#define INA226_CAL_REG		0x05
#define INA226_MASKEN_REG	0x06
#define INA226_ALERT_LMT_REG	0x07
#define INA226_MANUFACTURER_ID	0xFE
#define INA226_DIE_ID		0xFF

#define INA226_SHUNT_VALUE  0.01

esp_err_t i2c_write_byte(uint8_t address, uint8_t command, uint8_t data);
esp_err_t i2c_write_short(uint8_t address, uint8_t command, uint16_t data);
esp_err_t i2c_write_buf(uint8_t address, uint8_t command, uint8_t *data, uint8_t len);
uint8_t i2c_read_byte(uint8_t address, uint8_t command);
uint16_t i2c_read_short( uint8_t address, uint8_t command);
esp_err_t i2c_read_buf( uint8_t address, uint8_t command, uint8_t *buffer, uint8_t len);

void ina226_init();
float ina226_voltage();
float ina226_current();
float ina226_power();

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
