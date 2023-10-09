#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{
    // printf("INA Hardware update to App\r\n");
    // HAL::INA2xx_Info_t info;
    // info.cmd = HAL::INA_UPDATE;
    // HAL::INA2xx_GetInfo(&info);
    // // info.voltage = 11.23;
    // account->Commit(&info, sizeof(HAL::INA2xx_Info_t));
    // account->Publish();
}

static int onEvent(Account* account, Account::EventParam_t* param)
{

    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return Account::ERROR_NONE;
    }

    // if (param->event != Account::EVENT_SUB_PULL)
    // {
    //     return Account::ERROR_UNSUPPORTED_REQUEST;
    // }

    if (param->size != sizeof(HAL::INA2xx_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::INA2xx_Info_t *info = (HAL::INA2xx_Info_t *)(param->data_p);
    // printf("INA2xx hardwware event!!!\r\n");

    switch (info->cmd)
    {
        case HAL::INA_START:
            printf("INA start\n");
            HAL::INA2xx_Init();
            account->SetTimerEnable(1);
            break;
        case HAL::INA_UPDATE:
            // printf("INA update value");
            HAL::INA2xx_GetInfo(info);
            break;
        case HAL::INA_STOP:
            printf("INA stop\n");
            account->SetTimerEnable(0);
            HAL::INA2xx_Deinit();
            break;
        
        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(INA2xxHardware)
{
    account->Subscribe("PowerPDModel");
    account->SetEventCallback(onEvent);
    account->SetTimerPeriod(200);
    account->SetTimerEnable(0);
}
