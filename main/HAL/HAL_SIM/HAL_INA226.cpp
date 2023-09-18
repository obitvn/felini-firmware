#include <cstdio>
#include "HAL.h"
#include "stdio.h"



/* DAP Link*/
void HAL::INA2xx_Init()
{
    printf("ina init\r\n");
    // INA2xx_start();
}
void HAL::INA2xx_GetInfo(INA2xx_Info_t *info)
{

}

void HAL::INA2xx_Deinit()
{
    printf("ina Deinit\r\n");
}