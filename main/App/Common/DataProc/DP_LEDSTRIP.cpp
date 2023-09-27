#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{
    printf("LED Strip Hardware update to App\r\n");
}

static int onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_NOTIFY)
    {
        printf("Account::ERROR_UNSUPPORTED_REQUEST\r\n");
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::LEDSTRIP_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::LEDSTRIP_Info_t *info = (HAL::LEDSTRIP_Info_t *)param->data_p;
    printf("led strip event!!!\r\n");

    switch (info->cmd)
    {
        case HAL::CMD_START:
            HAL::LEDSTRIP_Init();
            break;

        case HAL::CMD_UPDATE:
            HAL::LEDSTRIP_Update(info);
            break;

        case HAL::CMD_STOP:
            HAL::LEDSTRIP_Deinit();

        default:
            break;
    }

    return 0;
}

DATA_PROC_INIT_DEF(LEDSTRIPHardware)
{
    account->Subscribe("ColorWheelModel");
    account->SetEventCallback(onEvent);
}
