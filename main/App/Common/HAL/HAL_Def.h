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
    typedef enum
    {
        PD_PDO_TYPE_FIXED_SUPPLY = 0,
        PD_PDO_TYPE_BATTERY = 1,
        PD_PDO_TYPE_VARIABLE_SUPPLY = 2, // USB PD PPS
        PD_PDO_TYPE_AUGMENTED_PDO = 3,   /* USB PD 3.0 */
        PD_PDO_NOT_CONNECT = 4
    } PowerPD_type_t;

    typedef enum
    {
        PD_PDO_OFF = 0,
        PD_PDO_ON = 1,
        PD_PDO_INIT = 2,
        PD_PDO_DENIT = 3,
        PD_PDO_SETUP = 4,
        PD_PDO_UPDATE = 5       
    } PowerPD_cmd_t;


    typedef struct
    {
        uint16_t min_voltage;
        uint16_t max_voltage;
        uint16_t max_current;
        uint16_t max_power;
        uint16_t set_voltage;
        uint16_t set_current;
        PowerPD_type_t pd_type;
        PowerPD_cmd_t pd_cmd;
    } PowerPD_Info_t;

    

    /*RC Servo*/
    typedef enum
    {
        SERVO_CMD_INIT,
        SERVO_CMD_UPDATE,
        SERVO_CMD_Deinit,
    } RCServo_Cmd_t;

    typedef struct
    {
        RCServo_Cmd_t cmd;
        int16_t angle;
        uint8_t mode;
        int16_t min_degree; // Minimum angle
        int16_t max_degree;
        uint16_t min_pulse_with; // Minimum pulse width in microsecond
        uint16_t max_pulse_with;
    } RCServo_Info_t;



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

    /* DAPLink*/
    // typedef enum daplink_cmd
    // {
    //     DAP_START = 0,
    //     DAP_STOP,
    // } daplink_cmd_t;

    typedef struct
    {
        uint16_t baudrate;
        uint8_t status;
        bool connect;
        bool running;
    } DAPLink_Info_t;
}

#endif
