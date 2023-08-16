#ifndef __Hertz_MODEL_H
#define __Hertz_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class HertzModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
