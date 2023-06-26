#include "PowerSupplyModel.h"

using namespace Page;

void PowerSupplyModel::Init()
{
    account = new Account("PowerSupplyModel", DataProc::Center(), 0, this);
    account->Subscribe("StatusBar");
    account->Subscribe("WiFi");
    account->Subscribe("PowerSupply");
    account->SetEventCallback(onEvent);
}

void PowerSupplyModel::Deinit()
{
    if (account)
    {
        delete account;
        account = nullptr;
    }
}

bool PowerSupplyModel::GetWiFiStatus()
{
    HAL::WiFi_Info_t wifi;
    account->Pull("WiFi", &wifi, sizeof(wifi));
    return wifi.isConnected;
}

int PowerSupplyModel::PowerSupplyStatusUpdate()
{
    return account->Pull("PowerSupply", &powersupply, sizeof(powersupply));
}

int PowerSupplyModel::onEvent(Account *account, Account::EventParam_t *param)
{
    if (param->event != Account::EVENT_PUB_PUBLISH)
    {
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }
    return 0;
}