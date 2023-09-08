#include "PowerSupplyModel.h"
#include "stdio.h"


using namespace Page;

void PowerSupplyModel::Init()
{
    account = new Account("PowerPDModel", DataProc::Center(), 0, this);
    account->Subscribe("PowerPD");
    account->Subscribe("INA2xxHardware");
    account->SetEventCallback(onEvent);

    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_INIT;
    info_val.set_voltage = 5000;
    info_val.set_current = 1000;
    account->Notify("PowerPD", &info_val, sizeof(info_val));

    HAL::INA2xx_Info_t ina_info;
    ina_info.cmd = HAL::INA_START;
    account->Notify("INA2xxHardware", &ina_info, sizeof(ina_info));
}

void PowerSupplyModel::Deinit()
{
    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_DENIT;
    info_val.set_voltage = 0;
    info_val.set_current = 0;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
    HAL::INA2xx_Info_t ina_info;
    ina_info.cmd = HAL::INA_STOP;
    account->Notify("INA2xxHardware", &ina_info, sizeof(ina_info));
}

void PowerSupplyModel::PDSetUp(float voltage, float current, bool powctrl, PDSetUp_mode_t mode)
{
    HAL::PowerPD_Info_t info_val;
    
    switch (mode)
    {
        case PD_PDM_ON_OFF:
            if (powctrl)
            {
                info_val.pd_cmd = HAL::PD_PDO_ON;
                printf("volt %.3f, current %.3f\r\n", voltage, current);
                info_val.set_voltage = voltage*1000;
                info_val.set_current = current*1000;
            }
            else
            {
                info_val.pd_cmd = HAL::PD_PDO_OFF;
            }
            break;
        
        default:
            break;
    }
    account->Notify("PowerPD", &info_val, sizeof(HAL::PowerPD_Info_t));
}

void PowerSupplyModel::Update(HAL::PowerPD_Info_t *pd)
{

}

void PowerSupplyModel::GetPDInfo(HAL::PowerPD_Info_t *pd)
{
    memset(pd, 0, sizeof(HAL::PowerPD_Info_t));
    HAL::INA2xx_Info_t ina;
    if (account->Pull("INA2xxHardware", &ina, sizeof(HAL::INA2xx_Info_t)) != Account::ERROR_NONE)
    {
        return;
    }
    pd->get_voltage = ina.voltage;
}

int PowerSupplyModel::onTimer(Account *account)
{
    return 1;
}

int PowerSupplyModel::onEvent(Account *account, Account::EventParam_t *param)
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