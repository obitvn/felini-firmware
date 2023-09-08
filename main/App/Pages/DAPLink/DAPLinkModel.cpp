#include "DAPLinkModel.h"
#include "stdio.h"

using namespace Page;

void DAPLinkModel::Init()
{
    account = new Account("DAPLinkModel", DataProc::Center(), 0, this);
    account->Subscribe("DAPLinkHardware");
    account->SetEventCallback(onEvent);
}

void DAPLinkModel::Deinit()
{

}

void DAPLinkModel::DAPCommand(int cmd)
{
    HAL::DAPLink_Info_t info;
    if(cmd)
    {
        info.cmd = HAL::DAP_START;
    } 
    else 
    {
        info.cmd = HAL::DAP_STOP;
        printf("dap stop cmd\n");
    }
    account->Notify("DAPLinkHardware", &info, sizeof(HAL::DAPLink_Info_t));
}


int DAPLinkModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}