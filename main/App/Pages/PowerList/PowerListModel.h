#ifndef __PowerList_MODEL_H
#define __PowerList_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class PowerListModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
