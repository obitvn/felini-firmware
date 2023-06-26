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

    /* Power */
    typedef struct
    {
        uint16_t voltage;
        uint8_t usage;
        bool isCharging;
    } Power_Info_t;

    /* WiFi */
    typedef struct
    {
        bool isConnected;
        char ip_str[32];
    } WiFi_Info_t;

    /* Weather */
    typedef struct
    {
        int8_t code;
        char summary[16];
        float temperature;
        char last_update[128];
    } Weather_Info_t;

    typedef struct
    {
        int8_t code;
        char summary[16];
        float temperature;
        char last_update[128];
    } PowerSupply_Info_t;
}

#endif
