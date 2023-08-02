#ifndef __HAL_DEF_H
#define __HAL_DEF_H

#include <stdint.h>

namespace HAL
{

    /* Clock */
    typedef struct
    {
        uint16_t year;
        uint8_t month;
        uint8_t day;
        uint8_t week;
        uint8_t hour;
        uint8_t minute;
        uint8_t second;
        uint16_t millisecond;
    } Clock_Info_t;

    /* IMU */
    typedef struct
    {
        int16_t ax;
        int16_t ay;
        int16_t az;
        int16_t gx;
        int16_t gy;
        int16_t gz;
        int16_t steps;
    } IMU_Info_t;

    /* Power Delivery*/
    typedef struct
    {
        uint16_t min_voltage;
        uint16_t max_voltage;
        uint16_t max_current;
        uint16_t max_power;
        uint16_t pd_type;
    } PowerPD_Info_t;

    /* Power PMIC*/
    typedef struct
    {
        uint16_t voltage;
        uint8_t usage;
        bool isCharging;
        float charge_current;
        float discharge_current;
        float temp;
    } PowerPMIC_Info_t;


}

#endif
