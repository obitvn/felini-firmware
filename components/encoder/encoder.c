#include "encoder.h"

static rotary_encoder_t *encoder = NULL; /* Encoder */
static SemaphoreHandle_t mutex = NULL;

static int32_t last_cnt;                    /* Encoder last count value */
static int32_t encoder_diff = 0;            /* Encoder rotation direction, 0 is stationary, 1 is clockwise rotation, -1 is counterclockwise rotation */
static bool encoder_diff_disable = false;   /* Get the encoder value, true means enabled, false means disabled */

key_state_t encoder_push_state;

void input_task_create(void);

/* Encoder configuration */
void encoder_config(void)
{
    uint32_t pcnt_unit = 0;

    input_task_create();

    mutex = xSemaphoreCreateMutex();

    /* 1. Configure encoder KEY GPIO */
    gpio_config_t io_conf = {
        .intr_type = GPIO_INTR_DISABLE,                
        .pin_bit_mask = ENCODER_PUSH_GPIO_PIN_SEL,
        .mode = GPIO_MODE_INPUT,
        .pull_down_en = 1,                              /* Allow dropdown */
        .pull_up_en = 0,
    };

    gpio_config(&io_conf);

    /* 2. Configure encoders A and B */
    rotary_encoder_config_t config = ROTARY_ENCODER_DEFAULT_CONFIG((rotary_encoder_dev_t)pcnt_unit, ENCODER_A_PIN, ENCODER_B_PIN);
    ESP_ERROR_CHECK(rotary_encoder_new_ec11(&config, &encoder));
    ESP_ERROR_CHECK(encoder->set_glitch_filter(encoder, 1));    /* filter */
    ESP_ERROR_CHECK(encoder->start(encoder));

    last_cnt = encoder->get_counter_value(encoder);             /* Get the initial value of the encoder */
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
            /* 1.KEY detection */
            encoder_push_state = encoder_push_scan();

            /* 2. Direction detection */
            if(!encoder_diff_disable)
            {
                int32_t dir = 0;
                int32_t cnt = encoder->get_counter_value(encoder); /* Get encoder value */

                /* Direction judgment */
                if(cnt - last_cnt < 0 && cnt - last_cnt <= -3)
                {
                    dir = -1;                   /* Anticlockwise rotation */
                }
                else if(cnt - last_cnt > 0 && cnt - last_cnt >= 3)
                {
                    dir = 1;                    /* clockwise rotation */
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
    xTaskCreate(encoder_task, "input task", 1024, NULL, 1, NULL);
}

void encoder_set_diff(int value)
{
    encoder_diff = encoder_diff + value;
}

int32_t encoder_get_diff(void)
{
    int32_t diff = encoder_diff;
    encoder_diff = 0;
    return diff;
}

bool encoder_get_is_push(void)
{
    /* The direction value will no longer be read when the encoder KEY is pressed */
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


