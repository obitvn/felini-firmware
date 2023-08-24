#include <cstdio>
#include "HAL.h"
#include "stdio.h"
#include "./dap_main.h"


/* DAP Link*/
void HAL::DAPLink_Init()
{
    printf("dap init\r\n");
    daplink_start();
}
void HAL::DAPLink_GetInfo(DAPLink_Info_t *info)
{
    info->baudrate = 921600;
    info->status = 12;
    info->connect = is_daplink_connect();
    info->running = is_daplink_running();
}

void HAL::DAPLink_Deinit()
{
    printf("dap Deinit\r\n");
    daplink_stop();
}