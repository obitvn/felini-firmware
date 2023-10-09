#include "AnalogViewerModel.h"

using namespace Page;

void AnalogViewerModel::Init()
{
    account = new Account("AnalogViewerModel", DataProc::Center(), 0, this);
    account->Subscribe("INA2xxHardware");
    account->Subscribe("PowerPD");
    account->SetEventCallback(onEvent);
    HAL::INA2xx_Info_t ina_info;
    ina_info.cmd = HAL::INA_START;
    account->Notify("INA2xxHardware", &ina_info, sizeof(ina_info));

    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_ON;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
}

void AnalogViewerModel::Deinit()
{
    HAL::INA2xx_Info_t ina_info;
    ina_info.cmd = HAL::INA_STOP;
    account->Notify("INA2xxHardware", &ina_info, sizeof(ina_info));

    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_OFF;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
}

void AnalogViewerModel::GetPDInfo(HAL::INA2xx_Info_t *ina)
{
    ina->cmd = HAL::INA_UPDATE;
    if (account->Pull("INA2xxHardware", ina, sizeof(HAL::INA2xx_Info_t)) != Account::ERROR_NONE)
    {
        return;
    }
}

int AnalogViewerModel::onTimer(Account *account)
{
    return 1;
}

int AnalogViewerModel::onEvent(Account *account, Account::EventParam_t *param)
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

    if (param->size != sizeof(HAL::INA2xx_Info_t))
    {
        return Account::ERROR_SIZE_MISMATCH;
    }

    return 1;
}