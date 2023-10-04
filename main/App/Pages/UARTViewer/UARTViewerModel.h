#ifndef __UARTViewer_MODEL_H
#define __UARTViewer_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class UARTViewerModel
{
public:
    void Init();
    void Deinit();
    void Update(HAL::UART_Info_t *uart);

private:
    Account* account;

private:
    static int onEvent(Account *account, Account::EventParam_t *param);
    static int onTimer(Account *account);

    
};

}

#endif
