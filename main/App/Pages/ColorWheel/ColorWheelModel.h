#ifndef __ColorWheel_MODEL_H
#define __ColorWheel_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class ColorWheelModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
