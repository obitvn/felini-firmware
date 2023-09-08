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

/* DAP Link*/
void HAL::INA2xx_Init()
{
    printf("Ina226 init\r\n");
    ina226_init_desc(NULL, 1, (i2c_port_t)1, (gpio_num_t)1, (gpio_num_t)1);
    ina226_set_config(NULL, INA226_MODE_TRIG_SHUNT_BUS, INA226_AVG_128,
            INA226_CT_1100, INA226_CT_1100);
}
void HAL::INA2xx_GetInfo(INA2xx_Info_t *info)
{
    ina226_get_bus_voltage(NULL, &info->voltage);
    ina226_get_current(NULL, &info->current);
    ina226_get_power(NULL, &info->power);
}

void HAL::INA2xx_Deinit()
{
    printf("Ina226 Deinit\r\n");

}