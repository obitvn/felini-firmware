#include <cstdio>
#include "HAL.h"
#include "stdio.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"

#include "ina226.h"

INA226_WE ina226;

/* DAP Link*/
void HAL::INA2xx_Init()
{
    float shuntVoltage_mV = 0.0;
    float loadVoltage_V = 0.0;
    float busVoltage_V = 0.0;
    float current_mA = 0.0;
    float power_mW = 0.0;

    printf("Ina226 init\r\n");
    ina226.init();
    ina226.setResistorRange(0.01, 10.0);  // choose resistor 5 mOhm and gain range up to 10 A
    ina226.waitUntilConversionCompleted(); // if you comment this line the first data might be zero

    ina226.readAndClearFlags();
    shuntVoltage_mV = ina226.getShuntVoltage_mV();
    busVoltage_V = ina226.getBusVoltage_V();
    current_mA = ina226.getCurrent_mA();
    power_mW = ina226.getBusPower();
    loadVoltage_V = busVoltage_V + (shuntVoltage_mV / 1000);

    printf("Shunt Voltage [mV]: %f\n", shuntVoltage_mV);
    printf("Bus Voltage [V]: %f\n", busVoltage_V);
    printf("Load Voltage [V]: %f\n", loadVoltage_V);
    printf("Current[mA]: %f\n", current_mA);
    printf("Bus Power [mW]: %f\n", power_mW);

}
void HAL::INA2xx_GetInfo(INA2xx_Info_t *info)
{
    info->voltage = ina226.getBusVoltage_V();
    info->current = ina226.getCurrent_mA();
    info->power = ina226.getBusPower();

    // printf("volt %f cur %f pow %f\n", info->voltage, info->current, info->power);
}

void HAL::INA2xx_Deinit()
{
    printf("Ina226 Deinit\r\n");

}