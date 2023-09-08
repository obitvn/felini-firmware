#include <cstdio>
#include "HAL.h"
#include "stdio.h"

//esp32-s3
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include <ina226.h>
#include <string.h>

static const char *TAG = "ina226";



/* PowerMeasure*/
void HAL::PowerMeasure_Init()
{
    

}
void HAL::PowerMeasure_GetInfo(PowerMeasure_Info_t *info)
{

}

void HAL::PowerMeasure_Update(PowerMeasure_Info_t *info)
{
}

void HAL::PowerMeasure_Deinit()
{

}