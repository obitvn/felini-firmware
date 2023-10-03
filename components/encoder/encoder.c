#include "encoder.h"
#include "esp_log.h"
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"


static SemaphoreHandle_t mutex = NULL;

static int32_t last_cnt;                    /* Encoder last count value */
static int32_t encoder_diff = 0;            /* Encoder rotation direction, 0 is stationary, 1 is clockwise rotation, -1 is counterclockwise rotation */
static bool encoder_diff_disable = false;   /* Get the encoder value, true means enabled, false means disabled */

key_state_t encoder_push_state;

pcnt_unit_handle_t pcnt_unit_encoder = NULL;

void input_task_create(void);


void pcnt_config(int chanel_A, int chanel_B)
{

    pcnt_unit_config_t unit_config = {
        .high_limit = 10000,
        .low_limit = -10000,
    };

    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit_encoder));


    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 8000,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit_encoder, &filter_config));

    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = chanel_A,
        .level_gpio_num = chanel_B,
    };
    pcnt_channel_handle_t pcnt_chan_a = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit_encoder, &chan_a_config, &pcnt_chan_a));

    pcnt_chan_config_t chan_b_config = {
        .edge_gpio_num = chanel_B,
        .level_gpio_num = chanel_A,
    };
    pcnt_channel_handle_t pcnt_chan_b = NULL;
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit_encoder, &chan_b_config, &pcnt_chan_b));

    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_DECREASE, PCNT_CHANNEL_EDGE_ACTION_INCREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_a, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_b, PCNT_CHANNEL_EDGE_ACTION_INCREASE, PCNT_CHANNEL_EDGE_ACTION_DECREASE));
    ESP_ERROR_CHECK(pcnt_channel_set_level_action(pcnt_chan_b, PCNT_CHANNEL_LEVEL_ACTION_KEEP, PCNT_CHANNEL_LEVEL_ACTION_INVERSE));

    pcnt_unit_enable(pcnt_unit_encoder);
    pcnt_unit_clear_count(pcnt_unit_encoder);
    pcnt_unit_start(pcnt_unit_encoder);
}

int32_t get_value_encoder(void)
{
    int32_t pulse_count;
    pcnt_unit_get_count(pcnt_unit_encoder, &pulse_count);
    return pulse_count;
}

/* Encoder configuration */
void encoder_config(void)
{

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
    // rotary_encoder_config_t config = ROTARY_ENCODER_DEFAULT_CONFIG((rotary_encoder_dev_t)&pcnt_unit_encoder, ENCODER_A_PIN, ENCODER_B_PIN);
    // ESP_ERROR_CHECK(rotary_encoder_new_ec11(&config, &encoder));
    // ESP_ERROR_CHECK(encoder->set_glitch_filter(encoder, 1));    /* filter */
    // ESP_ERROR_CHECK(encoder->start(encoder));

    pcnt_config(ENCODER_B_PIN, ENCODER_A_PIN);

    last_cnt = get_value_encoder();             /* Get the initial value of the encoder */
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
                int32_t cnt = get_value_encoder(); /* Get encoder value */

                /* Direction judgment */
                if(cnt - last_cnt < 0 && cnt - last_cnt <= -2)
                {
                    dir = -1;                   /* Anticlockwise rotation */
                }
                else if(cnt - last_cnt > 0 && cnt - last_cnt >= 2)
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


