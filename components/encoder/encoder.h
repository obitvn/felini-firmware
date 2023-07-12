#ifndef __MY_ENCODER_H
#define __MY_ENCODER_H

#include "rotary_encoder.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"

typedef enum key_state {
    KEY_UP = 0,                             /* 编码器按键弹起状态 */
    KEY_DOWN,                               /* 编码器按键按下状态 */
}key_state_t;

#define ENCODER_A_PIN       33          /* 编码器A端 */
#define ENCODER_B_PIN       34          /* 编码器B端 */
#define ENCODER_PUSH_PIN    35          /* 编码器KEY端 */
#define ENCODER_PUSH_GPIO_PIN_SEL   (1ULL << ENCODER_PUSH_PIN)      /* 编码器KEY GPIO bit 掩码 */

void encoder_config(void);              /* 编码器配置 */
void input_task_create(void);         /* 编码器任务创建 */
int32_t encoder_get_diff(void);         /* 获取编码器值 */
bool encoder_get_is_push(void);         /* 获取编码器KEY是否按下值 */

#endif