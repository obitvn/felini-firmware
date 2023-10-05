#include "IICDiscoveryModel.h"

using namespace Page;

void IICDiscoveryModel::Init()
{
    account = new Account("IICDiscoveryModel", DataProc::Center(), 0, this);
    account->Subscribe("IICHardware");
    HAL::IIC_Info_t iic_info;
    iic_info.cmd = HAL::CMD_START;
    account->Notify("IICHardware", &iic_info, sizeof(iic_info));
}

void IICDiscoveryModel::Deinit()
{
    HAL::IIC_Info_t iic_info;
    iic_info.cmd = HAL::CMD_STOP;
    account->Notify("IICHardware", &iic_info, sizeof(iic_info));
}

int IICDiscoveryModel::Scan(HAL::IIC_Info_t *iic_info)
{
    iic_info->cmd = HAL::CMD_UPDATE;
    if (account->Pull("IICHardware", iic_info, sizeof(HAL::IIC_Info_t)) != Account::ERROR_NONE)
    {
        return 1;
    }
    else return 0;
}