#include <cstdio>
#include "HAL.h"


#define TAG "PD HAL"



void HAL::PowerPD_Init()
{

}

void HAL::PowerPD_Deinit()
{


}

void HAL::PowerPD_PowerOn()
{

}

void HAL::PowerPD_PowerOff()
{

}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void HAL::PowerPD_Update(PowerPD_Info_t *pd_info)
{
    srand(time(NULL));
    pd_info->get_voltage = rand() % 20001;
    pd_info->get_current = rand() % 1001;
    ;
}

void HAL::PowerPD_Config(PowerPD_Info_t *pd_info)
{
}

void HAL::PowerPD_GetInfo(PowerPD_Info_t *info)
{
}
