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

    /* Power */
    void Power_Init();
    void Power_GetInfo(Power_Info_t *info);

    /* Power */
    void PowerSupply_Init();
    void PowerSupply_GetInfo(Power_Info_t *info);

    /* Clock */
    void Clock_Init();
    void Clock_GetInfo(Clock_Info_t *info);
    void Clock_SetInfo(const Clock_Info_t *info);
    const char *Clock_GetWeekString(uint8_t week);

    /* WiFi */
    void WiFi_Init();
    void WiFi_GetInfo(WiFi_Info_t *info);

    /* Weather */
    void Weather_Init();
    void Weather_GetInfo(Weather_Info_t *info);

}

#endif // !__cplusplus
#endif
