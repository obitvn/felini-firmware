#ifndef __PowerList_MODEL_H
#define __PowerList_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

    class PowerListModel
    {

    public:
        typedef enum
        {
            PD_PDM_ON_OFF = 0,
            PD_PDM_ON_CONFIG = 1,
            PD_PDM_OFF_CONFIG = 2,
        } PDSetUp_mode_t;

    public:
        void Init();
        void Deinit();
        void PDCMD(float voltage, float current, bool powctrl);

    public:
        HAL::PowerPD_Info_t PDInfo;

    private:
        Account *account;

    private:
        static int onEvent(Account *account, Account::EventParam_t *param);
        static int onTimer(Account *account);
    };

}

#endif
