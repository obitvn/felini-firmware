#ifndef _LOGICANALYZER_H__
#define _LOGICANALYZER_H__


#include <stdint.h>
#include "logic_analyzer_sump.h"


#ifdef __cplusplus
extern "C"
{
#endif


    int logic_analyzer_cdc_start(void);
    int logic_analyzer_cdc_stop(void);
    void logic_analyzer_cdc_read(const uint8_t *data, uint32_t data_len);
    void logic_analyzer_cdc_write(const uint8_t *data, uint32_t data_len);

#ifdef __cplusplus
}
#endif

#endif