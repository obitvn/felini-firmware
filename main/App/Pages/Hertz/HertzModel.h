#ifndef __Hertz_MODEL_H
#define __Hertz_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class HertzModel
{
public:
    void Init();
    void Deinit();
    void Update(uint32_t frequency, uint8_t duty);

private:
    Account* account;

private:
    static int onEvent(Account *account, Account::EventParam_t *param);
    static int onTimer(Account *account);
};

}

#endif
