#ifndef __MenuList_MODEL_H
#define __MenuList_MODEL_H

#include "Common/DataProc/DataProc.h"

namespace Page
{

    class MenuListModel
    {
    public:


    public:
        void Init();
        void Deinit();
        bool GetWiFiStatus();
        int MenuListStatusUpdate();

    private:
        Account *account;

    private:
        static int onEvent(Account *account, Account::EventParam_t *param);
    };

}

#endif
