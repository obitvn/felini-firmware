#include "DataProc.h"
#include "../HAL/HAL.h"

#include "stdio.h"

static void onTimer(Account* account)
{
    printf("Servo Hardware update to App\r\n");
}

static int onEvent(Account* account, Account::EventParam_t* param)
{
    if (param->event != Account::EVENT_NOTIFY)
    {
        printf("Account::ERROR_UNSUPPORTED_REQUEST\r\n");
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::RCServo_Info_t))
    {
        printf("Account::ERROR_SIZE_MISMATCH\r\n");
        return Account::ERROR_SIZE_MISMATCH;
    }

    HAL::RCServo_Info_t *info = (HAL::RCServo_Info_t *)param->data_p;
    printf("servo event!!!\r\n");

    switch (info->cmd)
    {
        case HAL::SERVO_CMD_INIT:
            HAL::RCServo_Init();
            break;

        case HAL::SERVO_CMD_UPDATE:
            HAL::RCServo_Update(info);
            break;

        case HAL::SERVO_CMD_SETUP:
            HAL::RCServo_SetFreq(info);
            break;

        case HAL::SERVO_CMD_Deinit:
            HAL::RCServo_Deinit();
            break;

        default:
            break;
    }
    
    
    // HAL::RCServo_Init();
    return 0;
}

DATA_PROC_INIT_DEF(RCServoHardware)
{
    account->Subscribe("RCServoModel");
    account->SetEventCallback(onEvent);

    
}
