#ifndef __I2C_AXP192_H__
#define __I2C_AXP192_H__

#include <stdint.h>
#include <stdbool.h>

#define I2C_AXP192_DEFAULT_ADDRESS 0x34

typedef struct {
  bool EXTEN;
  bool BACKUP;
  int DCDC1;
  int DCDC2;
  int DCDC3;
  int LDO2;
  int LDO3;
  int GPIO0;
  int GPIO1;
  int GPIO2;
  int GPIO3;
  int GPIO4;
} I2C_AXP192_InitDef;

class I2C_AXP192 {
  public:
    // I2C_AXP192(uint8_t deviceAddress = I2C_AXP192_DEFAULT_ADDRESS);
    void begin(I2C_AXP192_InitDef initDef);

    void setDCDC1(int voltage);
    void setDCDC2(int voltage);
    void setDCDC3(int voltage);

    void setLDO2(int voltage);
    void setLDO3(int voltage);

    void setGPIO0(int voltage);
    void setGPIO1(int voltage);
    void setGPIO2(int voltage);
    void setGPIO3(int voltage);
    void setGPIO4(int voltage);

    void setEXTEN(bool enable);
    void setBACKUP(bool enable);

    float getBatteryVoltage();
    float getBatteryDischargeCurrent();
    float getBatteryChargeCurrent();
    float getBatteryPower();
    float getAcinVolatge();
    float getAcinCurrent();
    float getVbusVoltage();
    float getVbusCurrent();
    float getInternalTemperature();
    float getApsVoltage();

    void powerOff();
    uint8_t getPekPress();

  private:
    uint8_t readByte(uint8_t address);
    void writeByte(uint8_t address, uint8_t data);
    void bitOn(uint8_t address, uint8_t bit);
    void bitOff(uint8_t address, uint8_t bit);


    int _deviceAddress;
};

#endif
