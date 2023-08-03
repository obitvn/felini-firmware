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
    account->Notify("DAPLinkHardware", &cmd, sizeof(cmd));
}


int DAPLinkModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}