#include <cstdio>
#include "HAL.h"

#define BATT_MIN_VOLTAGE 3300
#define BATT_MAX_VOLTAGE 4200
#define BATT_FULL_CHARGE_VOLTAGE 4100

typedef struct
{
    uint32_t LastHandleTime;
    uint16_t AutoLowPowerTimeout;
    bool AutoLowPowerEnable;
    bool IsShutdown;
    volatile uint16_t ADCValue;
} PowerSupply_t;

void HAL::PowerSupply_Init()
{
    // /* Initialize your hardware. */
    // axp192_init((const axp192_t *)i2c_hal(0));
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_GPIO0_SET_LEVEL, AXP192_HIGH); // M-Bus Power
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_GPIO1_SET_LEVEL, AXP192_LOW);  // Enable LED
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_GPIO2_SET_LEVEL, AXP192_LOW);  // Disable speaker
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_LDO2_SET_VOLTAGE, 3300);       // Set LDO2 LCD&TP voltage
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_LDO2_ENABLE);                  // Enable LDO2
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_GPIO4_SET_LEVEL, AXP192_LOW);  // LCD&TP Reset
    // vTaskDelay(100 / portTICK_PERIOD_MS);
    // axp192_ioctl((const axp192_t *)i2c_hal(0), AXP192_GPIO4_SET_LEVEL, AXP192_HIGH); // LCD&TP Hold
    // vTaskDelay(100 / portTICK_PERIOD_MS);
}

void HAL::PowerSupply_GetInfo(Power_Info_t *info)
{
    // static float axp_voltage = 0;
    // axp192_read((const axp192_t *)i2c_hal(0), AXP192_BATTERY_VOLTAGE, &axp_voltage);

    // int voltage = (int)(axp_voltage * 1000.0);
    // __LimitValue(voltage, BATT_MIN_VOLTAGE, BATT_MAX_VOLTAGE);

    // int usage = __Map(
    //                 voltage,
    //                 BATT_MIN_VOLTAGE, BATT_FULL_CHARGE_VOLTAGE,
    //                 0, 100
    //             );

    // __LimitValue(usage, 0, 100);

    // uint8_t change_status = 0;
    // axp192_read((const axp192_t *)i2c_hal(0), AXP192_CHARGE_STATUS, &change_status);
    // info->usage = usage;
    // info->isCharging = (change_status >> 7) & 0x01;
    // info->voltage = voltage;
}
