#ifndef __IMUSensor_MODEL_H
#define __IMUSensor_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class IMUSensorModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
