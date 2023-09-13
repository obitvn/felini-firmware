#ifndef __AnalogViewer_MODEL_H
#define __AnalogViewer_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class AnalogViewerModel
{
public:
    void Init();
    void Deinit();
    void GetPDInfo(HAL::INA2xx_Info_t *ina);

private:
    Account* account;

private:
    static int onEvent(Account *account, Account::EventParam_t *param);
    static int onTimer(Account *account);
};

}

#endif
