#include "IntervalModel.h"
#include "stdio.h"

using namespace Page;

void IntervalModel::Init()
{
    printf("IntervalModel::Init()\n");
    account = new Account("IntervalModel", DataProc::Center(), 0, this);
    account->Subscribe("IntervalTimeHardware");
    account->SetEventCallback(onEvent);
    HAL::IntervalTime_Info_t tick_info;
    tick_info.cmd = HAL::CMD_START;
    account->Notify("IntervalTimeHardware", &tick_info, sizeof(tick_info));
}

void IntervalModel::Deinit()
{
    printf("IntervalModel::DeInit()\n");
    HAL::IntervalTime_Info_t tick_info;
    tick_info.cmd = HAL::CMD_STOP;
    account->Notify("IntervalTimeHardware", &tick_info, sizeof(tick_info));
}

void IntervalModel::Update(HAL::IntervalTime_Info_t *tick)
{
    tick->cmd = HAL::CMD_UPDATE;
    if (account->Pull("IntervalTimeHardware", tick, sizeof(HAL::IntervalTime_Info_t)) != Account::ERROR_NONE)
    {
        return;
    }
}

int IntervalModel::onTimer(Account *account)
{
    return 1;
}

int IntervalModel::onEvent(Account *account, Account::EventParam_t *param)
{
    if (param->event == Account::EVENT_TIMER)
    {
        onTimer(account);
        return Account::ERROR_NONE;
    }
    if (param->event != Account::EVENT_SUB_PULL)
    {
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(HAL::IntervalTime_Info_t))
    {
        return Account::ERROR_SIZE_MISMATCH;
    }

    return 1;
}