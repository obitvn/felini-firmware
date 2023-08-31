#include "PowerSupplyModel.h"
#include "stdio.h"

using namespace Page;

void PowerSupplyModel::Init()
{
    account = new Account("PowerPDModel", DataProc::Center(), 0, this);
    account->Subscribe("PowerPD");
    account->SetEventCallback(onEvent);

    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_INIT;
    info_val.set_voltage = 5000;
    info_val.set_current = 1000;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
}

void PowerSupplyModel::Deinit()
{
    HAL::PowerPD_Info_t info_val;
    info_val.pd_cmd = HAL::PD_PDO_DENIT;
    info_val.set_voltage = 0;
    info_val.set_current = 0;
    account->Notify("PowerPD", &info_val, sizeof(info_val));
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
    account->Notify("PowerPD", &info_val, sizeof(info_val));
}

int PowerSupplyModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}