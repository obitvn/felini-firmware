#ifndef __Dialplate_MODEL_H
#define __Dialplate_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class DialplateModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
