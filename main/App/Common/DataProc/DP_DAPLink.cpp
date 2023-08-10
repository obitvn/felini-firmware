#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{
    printf("DAP Hardware update to App\r\n");
}

static int onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event == Account::EVENT_NOTIFY)
    {
        uint8_t data_val[12];
        memcpy(param->data_p, &data_val, param->size);
        printf("DAP App call Hardware value %d %s\r\n", data_val[0], data_val);
        if(data_val[0] == 18)
        {
            HAL::DAPLink_Init();
        }
        else if(data_val[0] == 0)
        {
            HAL::DAPLink_Denit();
        }
    }
    
    // HAL::DAPLink_Init();
    return 0;
}

DATA_PROC_INIT_DEF(DAPLinkHardware)
{
    account->Subscribe("DAPLinkModel");
    account->SetEventCallback(onEvent);
    // account->SetTimerPeriod(500);
    // account->SetTimerEnable(1);
    
}
