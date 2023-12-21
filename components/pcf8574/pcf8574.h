/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2018 Ruslan V. Uss <unclerus@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file pcf8574.h
 * @defgroup pcf8574 pcf8574
 * @{
 *
 * ESP-IDF driver for PCF8574 compatible remote 8-bit I/O expanders for I2C-bus
 *
 * Copyright (c) 2018 Ruslan V. Uss <unclerus@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */
#ifndef __PCF8574_H__
#define __PCF8574_H__

#include <stddef.h>
#include "i2c_manager.h"
#include <esp_err.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize device descriptor
 *
 * Default SCL frequency is 100kHz
 *
 * @param dev Pointer to I2C device descriptor
 * @param port I2C port number
 * @param addr I2C address (0b0100[A2][A1][A0] for PCF8574, 0b0111[A2][A1][A0] for PCF8574A)
 * @param sda_gpio SDA GPIO
 * @param scl_gpio SCL GPIO
 * @return `ESP_OK` on success
 */
esp_err_t pcf8574_init_desc(uint8_t addr);

/**
 * @brief Free device descriptor
 *
 * @param dev Pointer to I2C device descriptor
 * @return `ESP_OK` on success
 */


/**
 * @brief Read GPIO port value
 *
 * @param dev Pointer to I2C device descriptor
 * @param val 8-bit GPIO port value
 * @return `ESP_OK` on success
 */
esp_err_t pcf8574_port_read(uint8_t *val);

/**
 * @brief Write value to GPIO port
 *
 * @param dev Pointer to I2C device descriptor
 * @param value GPIO port value
 * @return ESP_OK on success
 */
esp_err_t pcf8574_port_write(uint8_t value);



esp_err_t pcf8574_init_desc(uint8_t address);


uint8_t pcf8574_read(uint8_t pin);


void pcf8574_write(uint8_t pin, uint8_t value);


void pcf8574_toggleMask(uint8_t mask);


void pcf8574_toggle(uint8_t pin);



#ifdef __cplusplus
}
#endif

/**@}*/

#endif /* __PCF8574_H__ */
