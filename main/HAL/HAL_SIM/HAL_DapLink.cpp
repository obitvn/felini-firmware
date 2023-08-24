#include <cstdio>
#include "HAL.h"
#include "stdio.h"


/* DAP Link*/
void HAL::DAPLink_Init()
{
    printf("dap init\r\n");
}
void HAL::DAPLink_GetInfo(DAPLink_Info_t *info)
{
    info->baudrate = 921600;
    info->status = 12;
    info->connect = 1;
    info->running = 0;
}

void HAL::DAPLink_Deinit()
{

}