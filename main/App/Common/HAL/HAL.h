/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __HAL_H
#define __HAL_H

#ifdef __cplusplus

#include <stdint.h>
#include "HAL_Def.h"

namespace HAL
{

    typedef bool (*CommitFunc_t)(void *info, void *userData);

    void HAL_Init();
    void HAL_Update();

    /* IMU */
    void IMU_Init();
    void IMU_SetCommitCallback(CommitFunc_t func, void *userData);
    void IMU_Update();

    /* Power Delivery*/
    void PowerPD_Init();
    void PowerPD_Update(PowerPD_Info_t *pd_info);
    void PowerPD_Config(PowerPD_Info_t *pd_info);
    void PowerPD_GetInfo(PowerPD_Info_t *info);
    void PowerPD_Deinit();
    void PowerPD_PowerOn();
    void PowerPD_PowerOff();

    /* Power PMIC*/
    void PowerPMIC_Init();
    void PowerPMIC_GetInfo(PowerPMIC_Info_t *info);

    /* Clock */
    void Clock_Init();
    void Clock_GetInfo(Clock_Info_t *info);
    void Clock_SetInfo(const Clock_Info_t *info);
    const char *Clock_GetWeekString(uint8_t week);

    /* DAP Link*/
    void DAPLink_Init();
    void DAPLink_GetInfo(DAPLink_Info_t *info);
    void DAPLink_Deinit();

    /* LogicAnalyzer*/
    void LogicAnalyzer_Init();
    void LogicAnalyzer_GetInfo(LogicAnalyzer_Info_t *info);
    void LogicAnalyzer_Deinit();

    /* INA2xx Link*/
    void INA2xx_Init();
    void INA2xx_GetInfo(INA2xx_Info_t *info);
    void INA2xx_Deinit();

    /*IIC Scan*/
    void IIC_Init();
    void IIC_Scan(IIC_Info_t *info);
    void IIC_GetInfo(IIC_Info_t *info);
    void IIC_Deinit();

    /* RCServo*/
    void RCServo_Init();
    void RCServo_GetInfo(RCServo_Info_t *info);
    void RCServo_SetFreq(RCServo_Info_t *info);
    void RCServo_Update(RCServo_Info_t *info);
    void RCServo_Deinit();

    /*LED Strip*/
    void LEDSTRIP_Init();
    void LEDSTRIP_GetInfo(LEDSTRIP_Info_t *info);
    void LEDSTRIP_Update(LEDSTRIP_Info_t *info);
    void LEDSTRIP_Deinit();

    /* PowerMeasure*/
    void PowerMeasure_Init();
    void PowerMeasure_GetInfo(PowerMeasure_Info_t *info);
    void PowerMeasure_Update(PowerMeasure_Info_t *info);
    void PowerMeasure_Deinit();

    /*Interval Time*/
    void IntervalTime_Init();
    void IntervalTime_GetInfo(IntervalTime_Info_t *info);
    void IntervalTime_Deinit();
    
    /*UART Viewer*/
    void UART_Init(UART_Info_t *info);
    void UART_Update(UART_Info_t *info);
    void UART_Deinit();

}

#endif // !__cplusplus
#endif
