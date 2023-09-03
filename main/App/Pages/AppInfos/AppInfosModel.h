#ifndef __SYSTEM_INFOS_MODEL_H
#define __SYSTEM_INFOS_MODEL_H

#include "Common/DataProc/DataProc.h"

namespace Page
{

class AppInfosModel
{
public:
    void Init();
    void Deinit();
    void SetStatusBarStyle(DataProc::StatusBar_Style_t style);

private:
    Account* account;

private:

};

}

#endif
