#include <cstdio>
#include "HAL.h"
#include "stdio.h"


#define IIC_SDA_PIN 2
#define IIC_SCL_PIN 3



void HAL::IIC_Init()
{
    printf("HAL sim iic init\n");
}

void HAL::IIC_Scan(IIC_Info_t *info)
{
}


void HAL::IIC_GetInfo(IIC_Info_t *info)
{

}

void HAL::IIC_Deinit()
{

}