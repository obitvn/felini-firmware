#include "LogicAnalyzerModel.h"
#include "stdio.h"

using namespace Page;

void LogicAnalyzerModel::Init()
{
    account = new Account("LogicAnalyzerModel", DataProc::Center(), 0, this);
    account->Subscribe("LogicAnalyzerHardware");
    account->SetEventCallback(onEvent);
}

void LogicAnalyzerModel::Deinit()
{

}

void LogicAnalyzerModel::LACommand(int cmd)
{
    HAL::LogicAnalyzer_Info_t info;
    if(cmd)
    {
        info.cmd = HAL::LA_START;
    } 
    else 
    {
        info.cmd = HAL::LA_STOP;
        printf("dap stop cmd\n");
    }
    account->Notify("LogicAnalyzerHardware", &info, sizeof(HAL::LogicAnalyzer_Info_t));
}


int LogicAnalyzerModel::onEvent(Account *account, Account::EventParam_t *param)
{
    return 1;
}