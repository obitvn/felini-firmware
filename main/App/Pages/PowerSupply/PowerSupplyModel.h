#ifndef __PowerSupply_MODEL_H
#define __PowerSupply_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class PowerSupplyModel
{
public:
    void Init();
    void Deinit();
    void PDSetUp(uint16_t voltage, uint16_t current, uint8_t powctrl);
    

private:
    Account* account;

private:
    static int onEvent(Account *account, Account::EventParam_t *param);
};

}

#endif
