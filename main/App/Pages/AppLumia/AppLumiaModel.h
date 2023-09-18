#ifndef __AppLumia_MODEL_H
#define __AppLumia_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class AppLumiaModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
