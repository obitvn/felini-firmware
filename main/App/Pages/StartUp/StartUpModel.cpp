#include "StartUpModel.h"

using namespace Page;

void StartupModel::Init()
{
    account = new Account("StartupModel", DataProc::Center(), 0, this);
}

void StartupModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}
