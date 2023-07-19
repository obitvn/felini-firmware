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

private:
    Account* account;
};

}

#endif
