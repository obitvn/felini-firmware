#ifndef __UARTViewer_MODEL_H
#define __UARTViewer_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class UARTViewerModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
