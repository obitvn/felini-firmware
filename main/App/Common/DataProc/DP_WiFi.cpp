#include "DataProc.h"
#include "../HAL/HAL.h"

static int onEvent(Account* account, Account::EventParam_t* param)
{
    HAL::WiFi_Info_t wifiInfo;
    HAL::WiFi_GetInfo(&wifiInfo);

    memcpy(param->data_p, &wifiInfo, param->size);
    return 0;
}

DATA_PROC_INIT_DEF(WiFi)
{
    account->SetEventCallback(onEvent);
}
