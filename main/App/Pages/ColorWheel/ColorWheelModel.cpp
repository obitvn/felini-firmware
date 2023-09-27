#include "ColorWheelModel.h"

using namespace Page;


void ColorWheelModel::Init()
{
    account = new Account("ColorWheelModel", DataProc::Center(), 0, this);
    account->Subscribe("LEDSTRIPHardware");
    account->SetEventCallback(onEvent);

    HAL::LEDSTRIP_Info_t info_val;
    info_val.cmd = HAL::CMD_START;
    account->Notify("LEDSTRIPHardware", &info_val, sizeof(info_val));
}

void ColorWheelModel::Deinit()
{
    HAL::LEDSTRIP_Info_t info_val;
    info_val.cmd = HAL::CMD_STOP;
    account->Notify("LEDSTRIPHardware", &info_val, sizeof(info_val));
}

#include "stdio.h"
void ColorWheelModel::Update(uint32_t r, uint32_t g, uint32_t b)
{
    HAL::LEDSTRIP_Info_t info_val;
    info_val.cmd   = HAL::CMD_UPDATE;
    info_val.red   = r;
    info_val.blue  = b;
    info_val.green = g;
    account->Notify("LEDSTRIPHardware", &info_val, sizeof(info_val));
}

int ColorWheelModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}