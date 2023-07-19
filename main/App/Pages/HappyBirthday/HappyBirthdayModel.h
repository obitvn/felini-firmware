#ifndef __HappyBirthday_MODEL_H
#define __HappyBirthday_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class HappyBirthdayModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
