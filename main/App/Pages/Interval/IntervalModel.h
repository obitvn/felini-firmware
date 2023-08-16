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

private:
    Account* account;
};

}

#endif
