#include "UARTViewerModel.h"

using namespace Page;

void UARTViewerModel::Init()
{
    account = new Account("UARTViewerModel", DataProc::Center(), 0, this);
    account->Subscribe("PowerPD");
    account->Subscribe("UARTHardware");
    account->SetEventCallback(onEvent);

    HAL::UART_Info_t info;
    info.baud = 115200;
    info.cmd  = HAL::CMD_START;
    account->Notify("UARTHardware", &info, sizeof(info));
}

void UARTViewerModel::Update(HAL::UART_Info_t *uart)
{
    if (account->Pull("UARTHardware", uart, sizeof(HAL::UART_Info_t)) != Account::ERROR_NONE)
    {
        return;
    }
}

void UARTViewerModel::Deinit()
{
    HAL::UART_Info_t info;
    info.baud = 115200;
    info.cmd = HAL::CMD_STOP;
    account->Notify("UARTHardware", &info, sizeof(info));
}

int UARTViewerModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}