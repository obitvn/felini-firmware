#ifndef __ColorWheel_MODEL_H
#define __ColorWheel_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class ColorWheelModel
{
public:
    void Init();
    void Deinit();
    void Update(uint32_t r, uint32_t g, uint32_t b);

private:
    Account* account;
    static int onEvent(Account *account, Account::EventParam_t *param);
};

}

#endif
