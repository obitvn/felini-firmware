#ifndef __CandleLight_MODEL_H
#define __CandleLight_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class CandleLightModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
