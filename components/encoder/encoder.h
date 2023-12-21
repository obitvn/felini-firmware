#ifndef __MY_ENCODER_H
#define __MY_ENCODER_H
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

typedef enum key_state
{
    KEY_UP = 0, /* Encoder button pop-up state */
    KEY_DOWN,   /* Encoder button pressed state */
} key_state_t;

#define ENCODER_A_PIN 38                /* Encoder A terminal */
#define ENCODER_B_PIN 39                /* Encoder B end */
#define ENCODER_PUSH_PIN 3              /* Encoder KEY */
#define ENCODER_PUSH_GPIO_PIN_SEL (1ULL << ENCODER_PUSH_PIN) /* Encoder KEY GPIO bit mask */

void encoder_config(void);            /* Encoder configuration */
void input_task_create(void);         /* Encoder task creation */
int32_t encoder_get_diff(void);       /* Get the encoder value */
bool encoder_get_is_push(void);       /* Obtain whether the encoder KEY is pressed */
void encoder_set_diff(int value);

#endif