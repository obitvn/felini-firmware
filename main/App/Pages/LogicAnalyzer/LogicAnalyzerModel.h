#ifndef __LogicAnalyzer_MODEL_H
#define __LogicAnalyzer_MODEL_H

#include "Common/DataProc/DataProc.h"
#include "Common/HAL/HAL.h"

namespace Page
{

class LogicAnalyzerModel
{
public:
    void Init();
    void Deinit();

private:
    Account* account;
};

}

#endif
