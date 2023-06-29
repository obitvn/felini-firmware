#include "encoder.h"

static rotary_encoder_t *encoder = NULL;    /* 编码器 */
static SemaphoreHandle_t mutex = NULL;

static int32_t last_cnt;                    /* 编码器上一次计数值 */
static int32_t encoder_diff = 0;            /* 编码器转动方向，0为静止，1为顺时针旋转，-1为逆时针旋转 */
static bool encoder_diff_disable = false;   /* 获取编码器数值，true为使能，false为失能 */


key_state_t encoder_push_state;

/* 编码器配置 */
void encoder_config(void)
{
    uint32_t pcnt_unit = 0;

    mutex = xSemaphoreCreateMutex();

    /* 1.配置编码器KEY GPIO */
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,                
        .pin_bit_mask = ENCODER_PUSH_GPIO_PIN_SEL,
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = 1,                              /* 允许下拉 */
        .pull_up_en = 0,
    };

    gpio_config(&io_conf);

    /* 2.配置编码器A、B */
    rotary_encoder_config_t config = ROTARY_ENCODER_DEFAULT_CONFIG((rotary_encoder_dev_t)pcnt_unit, ENCODER_A_PIN, ENCODER_B_PIN);
    ESP_ERROR_CHECK(rotary_encoder_new_ec11(&config, &encoder));
    ESP_ERROR_CHECK(encoder->set_glitch_filter(encoder, 1));    /* 滤波器 */
    ESP_ERROR_CHECK(encoder->start(encoder));

    last_cnt = encoder->get_counter_value(encoder);             /* 获取编码器初值 */
}

static key_state_t encoder_push_scan(void)
{
    if(gpio_get_level(ENCODER_PUSH_PIN) == 0)
    {
        vTaskDelay(pdMS_TO_TICKS(20));
        if(gpio_get_level(ENCODER_PUSH_PIN) == 0)
        {
            return KEY_DOWN;
        }
    }

    return KEY_UP;
}

static void encoder_task(void *pvParameter)
{
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(150));

        if(pdTRUE == xSemaphoreTake(mutex, portMAX_DELAY))
        {
            /* 1.KEY检测 */
            encoder_push_state = encoder_push_scan();
            
            /* 2.方向检测 */
            if(!encoder_diff_disable)
            {
                int32_t dir = 0;
                int32_t cnt = encoder->get_counter_value(encoder);      /* 获取编码器数值 */
                
                /* 方向判断 */
                if(cnt - last_cnt < 0 && cnt - last_cnt <= -3)
                {
                    dir = -1;                   /* 逆时针旋转 */
                }
                else if(cnt - last_cnt > 0 && cnt - last_cnt >= 3)
                {
                    dir = 1;                    /* 顺时针旋转 */
                }

                encoder_diff += dir;
                last_cnt = cnt;
            }

            xSemaphoreGive(mutex);
        }
    }
}

void input_task_create(void)
{
    xTaskCreatePinnedToCore(encoder_task, "input task", 1024, NULL, 1, NULL, 1);
}

int32_t encoder_get_diff(void)
{
    int32_t diff = encoder_diff;
    encoder_diff = 0;
    return diff;
}

bool encoder_get_is_push(void)
{
    /* 编码器KEY按下不再读取方向数值 */
    if(encoder_push_state == KEY_DOWN)
    {
        encoder_diff_disable = true;
        return true;
    }
    else
    {
        encoder_diff_disable = false;
        return false;
    }
}       


