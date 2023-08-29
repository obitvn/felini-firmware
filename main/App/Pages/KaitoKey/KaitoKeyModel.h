#ifndef __KaitoKey_MODEL_H
#define __KaitoKey_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class KaitoKeyModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
