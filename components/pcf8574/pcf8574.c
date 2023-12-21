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
 * @file pcf8574.c
 *
 * ESP-IDF driver for PCF8574 compatible remote 8-bit I/O expanders for I2C-bus
 *
 * Copyright (c) 2018 Ruslan V. Uss <unclerus@gmail.com>
 *
 * MIT Licensed as described in the file LICENSE
 */

#include <esp_err.h>
#include "pcf8574.h"

#include <stdio.h>
#include "esp_log.h"
#include "i2c_manager.h"


#define I2C_FREQ_HZ 100000

#define PCF8574_DEFAULT_I2C_ADDRESS 0x60

#define CHECK(x) do { esp_err_t __; if ((__ = x) != ESP_OK) return __; } while (0)
#define CHECK_ARG(VAL) do { if (!(VAL)) return ESP_ERR_INVALID_ARG; } while (0)
#define BV(x) (1 << (x))

static uint8_t addr=0;

static esp_err_t read_port(uint8_t *val)
{
    // CHECK_ARG(dev && val);

    // I2C_DEV_TAKE_MUTEX(dev);
    // I2C_DEV_CHECK(dev, i2c_dev_read(dev, NULL, 0, val, 1));
    // I2C_DEV_GIVE_MUTEX(dev);

    // return ESP_OK;
    return i2c_manager_read(I2C_NUM_0, PCF8574_DEFAULT_I2C_ADDRESS, 0, &val, 1);
}

static esp_err_t write_port(uint8_t val)
{
    // CHECK_ARG(dev);

    // I2C_DEV_TAKE_MUTEX(dev);
    // I2C_DEV_CHECK(dev, i2c_dev_write(dev, NULL, 0, &val, 1));
    // I2C_DEV_GIVE_MUTEX(dev);

    // return ESP_OK;
    return i2c_manager_write(I2C_NUM_0, PCF8574_DEFAULT_I2C_ADDRESS, 0, &val, 1);

}

///////////////////////////////////////////////////////////////////////////////

esp_err_t pcf8574_init_desc(uint8_t address)
{

    // CHECK_ARG(addr & 0x20);

    addr = address;
    return 1;
}



esp_err_t pcf8574_port_read(uint8_t *val)
{
    return read_port( val);
}

esp_err_t pcf8574_port_write(uint8_t val)
{
    return write_port( val);
}


uint8_t pcf8574_read(uint8_t pin)
{
  if (pin > 7)
  {
    return 0;
  }
  uint8_t _dataIn=0;
  pcf8574_port_read(&_dataIn); 
  return (_dataIn & (1 << pin)) > 0;
}


void pcf8574_write(uint8_t pin, uint8_t value)
{
  uint8_t _dataOut=0;
  if (pin > 7)
  {
    return;
  }
  if (value == 0)
  {
    _dataOut &= ~(1 << pin);
  }
  else
  {
    _dataOut |= (1 << pin);
  }
  pcf8574_port_write(_dataOut);
}

void pcf8574_toggleMask(uint8_t mask)
{
  uint8_t _dataOut=0;
  _dataOut ^= mask;
  pcf8574_port_write(_dataOut);
}


void pcf8574_toggle(uint8_t pin)
{
  if (pin > 7)
  {
    return;
  }
  pcf8574_toggleMask(1 << pin);
}

