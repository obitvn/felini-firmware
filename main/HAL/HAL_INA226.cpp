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
    ina226_init();
}
void HAL::INA2xx_GetInfo(INA2xx_Info_t *info)
{
    info->voltage = ina226_voltage();
    info->current = ina226_current();
    info->power   = ina226_power();
}

void HAL::INA2xx_Deinit()
{
    printf("Ina226 Deinit\r\n");

}