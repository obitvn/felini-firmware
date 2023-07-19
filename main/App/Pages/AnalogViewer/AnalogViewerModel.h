#ifndef __AnalogViewer_MODEL_H
#define __AnalogViewer_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class AnalogViewerModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
