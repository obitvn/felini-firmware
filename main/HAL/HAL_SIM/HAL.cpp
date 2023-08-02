#include "HAL.h"

void HAL::HAL_Init()
{
    // WiFi_Init();
    // Power_Init();
    // Clock_Init();
}

void HAL::HAL_Update()
{
    
}

extern "C" void Hal_init(void)
{
    HAL::HAL_Init();
}

extern "C" void Hal_update(void)
{
    HAL::HAL_Update();
}