#ifndef __PowerSupply_MODEL_H
#define __PowerSupply_MODEL_H

#include "Common/DataProc/DataProc.h"

namespace Page
{

    class PowerSupplyModel
    {
    public:
        HAL::PowerSupply_Info_t powersupply;

    public:
        void Init();
        void Deinit();
        bool GetWiFiStatus();
        int PowerSupplyStatusUpdate();

    private:
        Account *account;

    private:
        static int onEvent(Account *account, Account::EventParam_t *param);
    };

}

#endif
