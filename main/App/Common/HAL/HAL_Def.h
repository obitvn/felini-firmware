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

    typedef enum
    {
        STATUS_POWER_NA = 0,
        STATUS_POWER_TYP,
        STATUS_POWER_PPS
    } PowerPD_stt_t;

    typedef struct
    {
        uint16_t min_voltage;
        uint16_t max_voltage;
        uint16_t max_current;
        uint16_t max_power;
        uint16_t set_voltage;
        uint16_t set_current;
        float get_power; //mW
        float get_voltage; //mV
        float get_current; //mA
        PowerPD_type_t pd_type;
        PowerPD_cmd_t pd_cmd;
        PowerPD_stt_t pd_stt;
    } PowerPD_Info_t;

    

    /*RC Servo*/
    typedef enum
    {
        SERVO_CMD_INIT,
        SERVO_CMD_UPDATE,
        SERVO_CMD_SETUP,
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
        uint32_t frequency;
        uint8_t duty;
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
    typedef enum daplink_cmd
    {
        DAP_START = 0,
        DAP_UPDATE,
        DAP_STOP,
    } daplink_cmd_t;

    typedef struct
    {
        uint16_t baudrate;
        uint8_t status;
        bool connect;
        bool running;
        daplink_cmd_t cmd;
    } DAPLink_Info_t;

    typedef enum
    {
        CMD_START = 0,
        CMD_UPDATE,
        CMD_STOP,
        CMD_SEND,
        CMD_RECV,
        CMD_SETUP,
    } hal_cmd_t;

    typedef enum ina2xx_cmd
    {
        INA_START = 0,
        INA_UPDATE,
        INA_STOP,
    } ina2xx_cmd_t;

    typedef struct 
    {
        float voltage;
        float current;
        float power;
        uint16_t status;
        ina2xx_cmd_t cmd;
    } INA2xx_Info_t;

    typedef struct
    {
        uint8_t addr;
        bool status;
        hal_cmd_t cmd;
    } IIC_Info_t;

    typedef struct 
    {
        uint32_t baud;
        char *send;
        uint32_t send_length;
        char *receive;
        uint32_t recv_length;
        bool status;
        hal_cmd_t cmd;
    } UART_Info_t;

    typedef struct
    {
        uint8_t red;
        uint8_t green;
        uint8_t blue;
        bool status;
        hal_cmd_t cmd;
    } LEDSTRIP_Info_t;

    typedef struct 
    {
        /* data */
        uint32_t frequency;
        uint32_t time;
        hal_cmd_t cmd;
    } IntervalTime_Info_t;

    typedef struct
    {
        float volt;
        float current;
        float power;
        bool ready;
        bool alert;
        bool overflow;
    } PowerMeasure_Info_t;

    /* LogicAnalyzer*/
    typedef enum
    {
        LA_START = 0,
        LA_UPDATE,
        LA_STOP,
    } la_cmd_t;

    typedef struct
    {
        uint16_t baudrate;
        uint8_t status;
        bool connect;
        bool running;
        la_cmd_t cmd;
    } LogicAnalyzer_Info_t;
}

#endif
