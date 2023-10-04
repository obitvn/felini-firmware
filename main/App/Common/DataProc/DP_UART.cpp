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

    if (param->size != sizeof(HAL::UART_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::UART_Info_t *info = (HAL::UART_Info_t *)(param->data_p);

    switch (info->cmd)
    {
        case HAL::INA_START:
            printf("UART start.......\n");
            HAL::UART_Init(info);
            break;
        case HAL::INA_STOP:
            printf("UART stop\n");
            HAL::UART_Deinit();
            break;
        
        default:
            HAL::UART_Update(info);
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(UARTHardware)
{
    account->Subscribe("UARTViewerModel");
    account->SetEventCallback(onEvent);
}
