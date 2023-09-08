#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{
    printf("DAP Hardware update to App\r\n");
}

static int onEvent(Account* account, Account::EventParam_t* param)
{

    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return Account::ERROR_NONE;
    }
    if (param->event != Account::EVENT_NOTIFY)
    {
        printf("Account::ERROR_UNSUPPORTED_REQUEST\r\n");
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::DAPLink_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::DAPLink_Info_t *info = (HAL::DAPLink_Info_t *)(param->data_p);
    printf("DAPLink hardwware event!!!\r\n");

    switch (info->cmd)
    {
        case HAL::DAP_START:
            printf("Dap start\n");
            HAL::DAPLink_Init();
            break;
        case HAL::DAP_STOP:
            printf("DAP stop\n");
            HAL::DAPLink_Deinit();
            break;
        
        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(DAPLinkHardware)
{
    account->Subscribe("DAPLinkModel");
    account->SetEventCallback(onEvent);
    // account->SetTimerPeriod(500);
    // account->SetTimerEnable(1);
    
}
