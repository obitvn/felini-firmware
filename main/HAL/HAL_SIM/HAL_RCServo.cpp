#include <cstdio>
#include "HAL.h"
#include "stdio.h"



/* DAP Link*/
void HAL::RCServo_Init()
{
    printf("dap init\r\n");
    // RCServo_start();
}
void HAL::RCServo_GetInfo(RCServo_Info_t *info)
{
    // info->baudrate = 921600;
    // info->status = 12;
    // info->connect = is_RCServo_connect();
    // info->running = is_RCServo_running();
}

void HAL::RCServo_Update(RCServo_Info_t *info)
{

}

void HAL::RCServo_Deinit()
{
    printf("dap Deinit\r\n");
    // RCServo_stop();
}