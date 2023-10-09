#include "PowerListModel.h"
#include "stdio.h"

using namespace Page;

void PowerListModel::Init()
{
    account = new Account("PowerListModel", DataProc::Center(), 0, this);
    account->Subscribe("PowerPD");
    account->SetEventCallback(onEvent);

    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_INIT;
    info_val.set_voltage = 5000;
    info_val.set_current = 1000;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
}

void PowerListModel::PDCMD(float voltage, float current, bool powctrl)
{
    HAL::PowerPD_Info_t info_val;

    if (powctrl)
        {
            info_val.pd_cmd = HAL::PD_PDO_ON;
            printf("volt %.3f, current %.3f\r\n", voltage, current);
            info_val.set_voltage = voltage * 1000;
            info_val.set_current = current * 1000;
        }
    else
        {
            info_val.pd_cmd = HAL::PD_PDO_OFF;
        }


    account->Notify("PowerPD", &info_val, sizeof(HAL::PowerPD_Info_t));
    info_val.pd_cmd = HAL::PD_PDO_SETUP;
    account->Notify("PowerPD", &info_val, sizeof(HAL::PowerPD_Info_t));
}

void PowerListModel::Deinit()
{
    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_DENIT;
    info_val.set_voltage = 0;
    info_val.set_current = 0;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
}

int PowerListModel::onTimer(Account *account)
{
    return 1;
}

int PowerListModel::onEvent(Account *account, Account::EventParam_t *param)
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

    if (param->size != sizeof(HAL::PowerPD_Info_t))
    {
        return Account::ERROR_SIZE_MISMATCH;
    }

    return 1;
}