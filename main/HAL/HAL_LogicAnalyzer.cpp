#include <cstdio>
#include "HAL.h"
#include "stdio.h"
#include "logic_analyzer_sump.h"

/* DAP Link*/
void HAL::LogicAnalyzer_Init()
{
    printf("LogicAnalyzer init\r\n");
    logic_analyzer_sump();
}
void HAL::LogicAnalyzer_GetInfo(LogicAnalyzer_Info_t *info)
{

}

void HAL::LogicAnalyzer_Deinit()
{
    printf("LogicAnalyzer Deinit\r\n");
    logic_analyzer_sump_denit();
}