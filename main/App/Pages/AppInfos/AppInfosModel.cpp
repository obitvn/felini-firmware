#include "AppInfosModel.h"
#include <stdio.h>

using namespace Page;

void AppInfosModel::Init()
{
    account = new Account("AppInfosModel", DataProc::Center(), 0, this);
    account->Subscribe("StatusBar");
}

void AppInfosModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void AppInfosModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}
