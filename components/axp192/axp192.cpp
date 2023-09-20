#include "axp192.h"

#include <stdio.h>
#include "esp_log.h"
#include "i2c_manager.h"

static const char *TAG = "i2c-simple-example";

// I2C_AXP192::I2C_AXP192(uint8_t deviceAddress) {
//   _deviceAddress = deviceAddress;
// }


uint8_t I2C_AXP192::readByte(uint8_t address) {
  // _i2cPort->beginTransmission(_deviceAddress);
  // _i2cPort->write(address);
  // _i2cPort->endTransmission();
  // _i2cPort->requestFrom(_deviceAddress, 1);
  uint8_t val = 0;

  i2c_manager_read(I2C_NUM_0, I2C_AXP192_DEFAULT_ADDRESS, address, &val, 1);

  // ESP_LOGI("AXP192-dev", "readByte(%02X) = %02X", address, val);
  return val;
}

void I2C_AXP192::writeByte(uint8_t address, uint8_t data) {
  uint8_t buffer = data;
  i2c_manager_write(I2C_NUM_0, I2C_AXP192_DEFAULT_ADDRESS, address, &buffer, 1);

  // ESP_LOGI("AXP192-dev", "writeByte(%02X) = %02X", address, data);
}

void I2C_AXP192::begin(I2C_AXP192_InitDef initDef) {
  ESP_LOGD("AXP192", "Begin");

  setEXTEN(initDef.EXTEN);
  setBACKUP(initDef.BACKUP);

  setDCDC1(initDef.DCDC1);
  setDCDC2(initDef.DCDC2);
  setDCDC3(initDef.DCDC3);

  setLDO2(initDef.LDO2);
  setLDO3(initDef.LDO3);

  setGPIO0(initDef.GPIO0);
  setGPIO1(initDef.GPIO1);
  setGPIO2(initDef.GPIO2);
  setGPIO3(initDef.GPIO3);
  setGPIO4(initDef.GPIO4);

  writeByte(0x84, 0b11110010);  // ADC 200Hz
  writeByte(0x82, 0b11111111);  // ADC All Enable
  writeByte(0x33, 0b11000000);  // Charge 4.2V, 100mA
  writeByte(0x36, 0b00001100);  // PEK 128ms, PW OFF 4S
  writeByte(0x30, 0b10000000);  // VBUS Open
  writeByte(0x39, 0b11111100);  // Temp Protection
  writeByte(0x31, 0b00000100);  // Power Off 3.0V
}



void I2C_AXP192::bitOn(uint8_t address, uint8_t bit) {
  uint8_t add = address;
  uint8_t val = readByte(add) | bit;
  writeByte(add, val);
}

void I2C_AXP192::bitOff(uint8_t address, uint8_t bit) {
  uint8_t add = address;
  uint8_t val = readByte(add) & ~bit;
  writeByte(add, val);
}

void I2C_AXP192::setDCDC1(int voltage) {
  uint8_t add = 0x12;
  uint8_t val;

  if (voltage < 700 || 3500 < voltage) {
    // Disable
    bitOff(add, (1 << 0));
    return;
  } else {
    // Enable
    bitOn(add, (1 << 0));
  }

  // Set
  add = 0x26;
  val = ((voltage - 700) / 25) & 0x7f;
  writeByte(add, val);
}

void I2C_AXP192::setDCDC2(int voltage) {
  uint8_t add = 0x12;
  uint8_t val;

  if (voltage < 700 || 3500 < voltage) {
    // Disable
    bitOff(add, (1 << 4));
    return;
  } else {
    // Enable
    bitOn(add, (1 << 4));
  }

  // Set
  add = 0x23;
  val = ((voltage - 700) / 25) & 0x7f;
  writeByte(add, val);
}

void I2C_AXP192::setDCDC3(int voltage) {
  uint8_t add = 0x12;
  uint8_t val;

  if (voltage < 700 || 3500 < voltage) {
    // Disable
    bitOff(add, (1 << 1));
    return;
  } else {
    // Enable
    bitOn(add, (1 << 1));
  }

  // Set
  add = 0x27;
  val = ((voltage - 700) / 25) & 0x7f;
  writeByte(add, val);
}

void I2C_AXP192::setLDO2(int voltage) {
  uint8_t add = 0x12;
  uint8_t val;

  if (voltage < 1800 || 3300 < voltage) {
    // Disable
    bitOff(add, (1 << 2));
    return;
  } else {
    // Enable
    bitOn(add, (1 << 2));
  }

  // Set
  add = 0x28;
  val = readByte(add) & 0x0f;
  val |= (((voltage - 1800) / 100) & 0x0f ) << 4;
  writeByte(add, val);
}

void I2C_AXP192::setLDO3(int voltage) {
  uint8_t add = 0x12;
  uint8_t val;

  if (voltage < 1800 || 3300 < voltage) {
    // Disable
    bitOff(add, (1 << 3));
    return;
  } else {
    // Enable
    bitOn(add, (1 << 3));
  }

  // Set
  add = 0x28;
  val = readByte(add) & 0xf0;
  val |= (((voltage - 1800) / 100) & 0x0f );
  writeByte(add, val);
}

void I2C_AXP192::setEXTEN(bool enable) {
  uint8_t add = 0x12;

  if (enable) {
    // Enable
    bitOn(add, (1 << 6));
  } else {
    // Disable
    bitOff(add, (1 << 6));
  }
}

void I2C_AXP192::setBACKUP(bool enable) {
  uint8_t add = 0x35;

  if (enable) {
    // Enable
    bitOn(add, (1 << 7));
  } else {
    // Disable
    bitOff(add, (1 << 7));
  }
}

void I2C_AXP192::setGPIO0(int voltage) {
  uint8_t add = 0x90;
  uint8_t val;

  if (voltage < 1800 || 3300 < voltage) {
    // Set Mode
    writeByte(add, voltage);
  } else {
    // LDO
    writeByte(add, 0b00000010);

    // Set voltage
    add = 0x91;
    val = (((voltage - 1800) / 100) & 0x0f ) << 4;
    writeByte(add, val);
  }
}

void I2C_AXP192::setGPIO1(int voltage) {
}

void I2C_AXP192::setGPIO2(int voltage) {
}

void I2C_AXP192::setGPIO3(int voltage) {
}

void I2C_AXP192::setGPIO4(int voltage) {
}

float I2C_AXP192::getBatteryVoltage() {
  uint16_t val = readByte(0x78) << 4;
  val |= readByte(0x79);
  return val * 1.1;
}

float I2C_AXP192::getBatteryDischargeCurrent() {
  uint16_t val = readByte(0x7c) << 5;
  val |= readByte(0x7d);
  return val * 0.5;
}

float I2C_AXP192::getBatteryChargeCurrent() {
  uint16_t val = readByte(0x7a) << 5;
  val |= readByte(0x7b);
  return val * 0.5;
}

float I2C_AXP192::getBatteryPower() {
  uint32_t val = (readByte(0x70) << 16) | (readByte(0x71) << 8) | readByte(0x72);
  return  1.1 * 0.5 * val / 1000.0;
}

float I2C_AXP192::getAcinVolatge() {
  uint16_t val = readByte(0x56) << 4;
  val |= readByte(0x57);
  return val * 1.7;
}
float I2C_AXP192::getAcinCurrent() {
  uint16_t val = readByte(0x58) << 4;
  val |= readByte(0x59);
  return val * 0.625;
}

float I2C_AXP192::getVbusVoltage() {
  uint16_t val = readByte(0x5a) << 4;
  val |= readByte(0x5b);
  return val * 1.7;
}

float I2C_AXP192::getVbusCurrent() {
  uint16_t val = readByte(0x5c) << 4;
  val |= readByte(0x5d);
  return val * 0.375;
}

float I2C_AXP192::getInternalTemperature() {
  uint16_t val = readByte(0x5e) << 4;
  val |= readByte(0x5f);
  return -144.7 + val * 0.1;
}

float I2C_AXP192::getApsVoltage() {
  uint16_t val = readByte(0x7e) << 4;
  val |= readByte(0x7f);
  return val * 1.4;
}

void I2C_AXP192::powerOff() {
  bitOn(0x32, (1 << 7));
}

uint8_t I2C_AXP192::getPekPress() {
  uint8_t val = readByte(0x46);
  writeByte(0x46, 0x03);
  return val;
}
