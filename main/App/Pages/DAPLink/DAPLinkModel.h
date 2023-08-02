#ifndef __DAPLink_MODEL_H
#define __DAPLink_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class DAPLinkModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
