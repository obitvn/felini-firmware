#ifndef __PowerSupply_MODEL_H
#define __PowerSupply_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class PowerSupplyModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
