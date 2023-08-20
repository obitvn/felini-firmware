#ifndef __ServoCtrl_MODEL_H
#define __ServoCtrl_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class ServoCtrlModel
{
public:
    void Init();
    void Deinit();
    void ServoUpdateAngle(int16_t angle);

private : 
    Account *account;


private:
    static int onEvent(Account *account, Account::EventParam_t *param);
};

}

#endif
