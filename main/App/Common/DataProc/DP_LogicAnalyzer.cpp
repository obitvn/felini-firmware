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

    if (param->size != sizeof(HAL::LogicAnalyzer_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::LogicAnalyzer_Info_t *info = (HAL::LogicAnalyzer_Info_t *)(param->data_p);
    printf("LogicAnalyzer hardwware event!!!\r\n");

    switch (info->cmd)
    {
        case HAL::LA_START:
            printf("Logic start\n");
            HAL::LogicAnalyzer_Init();
            break;
        case HAL::LA_STOP:
            printf("Logic stop\n");
            HAL::LogicAnalyzer_Deinit();
            break;
        
        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(LogicAnalyzerHardware)
{
    account->Subscribe("LogicAnalyzerModel");
    account->SetEventCallback(onEvent);
    // account->SetTimerPeriod(500);
    // account->SetTimerEnable(1);
    
}
