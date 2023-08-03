#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{
    printf("DAP Hardware update to App\r\n");
}

static int onEvent(Account* account, Account::EventParam_t* param)
{
    printf("DAP App call Hardware\r\n");
    
    HAL::DAPLink_Init();
    return 0;
}

DATA_PROC_INIT_DEF(DAPLinkHardware)
{
    printf("DAP App call Hardware\r\n");
    account->Subscribe("DAPLinkModel");
    account->SetEventCallback(onEvent);
    // account->SetTimerPeriod(500);
    // account->SetTimerEnable(1);
    
}
