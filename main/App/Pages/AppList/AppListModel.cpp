#include "AppListModel.h"
#include <stdio.h>

using namespace Page;

void AppListModel::Init()
{
    account = new Account("AppListModel", DataProc::Center(), 0, this);
    account->Subscribe("StatusBar");
}

void AppListModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

void AppListModel::SetStatusBarStyle(DataProc::StatusBar_Style_t style)
{
    DataProc::StatusBar_Info_t info;
    DATA_PROC_INIT_STRUCT(info);

    info.cmd = DataProc::STATUS_BAR_CMD_SET_STYLE;
    info.param.style = style;

    account->Notify("StatusBar", &info, sizeof(info));
}
