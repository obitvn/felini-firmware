#include "DataProc.h"
#include "../HAL/HAL.h"

static int onEvent(Account* account, Account::EventParam_t* param)
{
    HAL::Weather_Info_t weatherInfo;
    HAL::Weather_GetInfo(&weatherInfo);

    memcpy(param->data_p, &weatherInfo, param->size);
    return 0;
}

DATA_PROC_INIT_DEF(Weather)
{
    account->SetEventCallback(onEvent);
}
