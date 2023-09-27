#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{

}

static int onEvent(Account* account, Account::EventParam_t* param)
{

    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return Account::ERROR_NONE;
    }

    if (param->event != Account::EVENT_SUB_PULL)
    {
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::IIC_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::IIC_Info_t *info = (HAL::IIC_Info_t *)(param->data_p);

    switch (info->cmd)
    {
        case HAL::CMD_START:
            printf("INA start\n");
            HAL::IIC_Init();
            account->SetTimerEnable(1);
            break;
        case HAL::CMD_UPDATE:
            printf("INA update value");
            HAL::IIC_Scan(info);
            break;
        case HAL::CMD_STOP:
            printf("INA stop\n");
            account->SetTimerEnable(0);
            HAL::IIC_Deinit();
            break;
        
        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(IICHardware)
{
    account->Subscribe("IICDiscoveryModel");
    account->SetEventCallback(onEvent);
    account->SetTimerPeriod(200);
    account->SetTimerEnable(0);
}
