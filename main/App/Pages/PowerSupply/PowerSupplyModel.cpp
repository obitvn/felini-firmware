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

void PowerSupplyModel::PDSetUp(uint16_t voltage, uint16_t current, bool powctrl, PDSetUp_mode_t mode)
{
    HAL::PowerPD_Info_t info_val;
    
    switch (mode)
    {
        case PD_PDM_ON_OFF:
            if (powctrl)
            {
                info_val.pd_cmd = HAL::PD_PDO_ON;
                // printf("volt %.3f, current %.3f\r\n", voltage, current);
                info_val.set_voltage = voltage;
                info_val.set_current = current;
            }
            else
            {
                info_val.pd_cmd = HAL::PD_PDO_OFF;
            }
            break;
        case PD_PDM_ON_CONFIG:
            {
                info_val.pd_cmd = HAL::PD_PDO_SETUP;
                printf("volt %d, current %d\r\n", voltage, current);
                info_val.set_voltage = voltage;
                info_val.set_current = current;
                break;
            }

        
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
    memset(&ina, 0, sizeof(HAL::INA2xx_Info_t));
    ina.cmd = HAL::INA_UPDATE;
    if (account->Pull("INA2xxHardware", &ina, sizeof(HAL::INA2xx_Info_t)) != Account::ERROR_NONE)
    {
        return;
    }
    pd->get_voltage = ina.voltage*1000;
    pd->get_current = ina.current/1000;
    pd->get_power   = ina.power/1000;
    
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