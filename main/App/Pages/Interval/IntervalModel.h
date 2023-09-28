#ifndef __Interval_MODEL_H
#define __Interval_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

    class IntervalModel
    {
    public:
        void Init();
        void Deinit();
        void Update(HAL::IntervalTime_Info_t *tick);

    private:
        Account *account;

    private:
        static int onEvent(Account *account, Account::EventParam_t *param);
        static int onTimer(Account *account);
    };

}

#endif
