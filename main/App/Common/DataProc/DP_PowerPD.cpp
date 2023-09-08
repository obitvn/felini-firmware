#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"



static void onTimer(Account* account)
{
    HAL::PowerPD_Info_t PDinfo;
    HAL::PowerPD_Update(&PDinfo);
    account->Commit(&PDinfo, sizeof(PDinfo));
    account->Publish();
    
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

    if (param->size != sizeof(HAL::PowerPD_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::PowerPD_Info_t *info = (HAL::PowerPD_Info_t *)param->data_p;
    printf("power pd event!!!\r\n");

    switch (info->pd_cmd)
    {
        case HAL::PD_PDO_INIT:
            HAL::PowerPD_Init();
            break;

        case HAL::PD_PDO_UPDATE:
            HAL::PowerPD_Update(info);
            break;

        case HAL::PD_PDO_DENIT:
            HAL::PowerPD_Deinit();
            break;

        case HAL::PD_PDO_OFF:
            HAL::PowerPD_PowerOff();
            break;

        case HAL::PD_PDO_ON:
            HAL::PowerPD_PowerOn();
            break;

        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(PowerPD)
{
    account->SetEventCallback(onEvent);
    account->SetTimerPeriod(100);
}
