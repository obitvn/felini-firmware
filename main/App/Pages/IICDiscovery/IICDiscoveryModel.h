#ifndef __IICDiscovery_MODEL_H
#define __IICDiscovery_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class IICDiscoveryModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
