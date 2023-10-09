
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/pcnt.h"
#include "driver/gpio.h"
#include "driver/rmt.h"
#include "esp_log.h"
#include "driver/pulse_cnt.h"
#include "driver/gpio.h"
#include "frequency_count.h"
#include "esp_timer.h"

#define TAG "frequency_counter"

#define PULSE_GPIO_INPUT 1
#define PULSE_PCNT_HIGH_LIMIT 32000
#define PULSE_SAMPLE_TIME (1000*1000)

pcnt_unit_handle_t pcnt_unit = NULL;
pcnt_unit_config_t unit_config = {
    .low_limit = -1,
    .high_limit = PULSE_PCNT_HIGH_LIMIT,
    .flags.accum_count = true, // enable counter accumulation

};
pcnt_channel_handle_t pcnt_chan_a = NULL;

esp_timer_handle_t oneshot_timer;
volatile uint32_t pulse_count=0;
volatile bool timer_mes = false;

static bool pulse_pcnt_on_reach(pcnt_unit_handle_t unit, const pcnt_watch_event_data_t *edata, void *user_ctx)
{
    // send event data to queue, from this interrupt callback
    // xQueueSendFromISR(queue, &(edata->watch_point_value), &high_task_wakeup);
    pulse_count += PULSE_PCNT_HIGH_LIMIT;
    return true;
}

static void pcnt_init(void)
{
    ESP_LOGI(TAG, "install pcnt unit");


    ESP_ERROR_CHECK(pcnt_new_unit(&unit_config, &pcnt_unit));

    ESP_LOGI(TAG, "set glitch filter");
    pcnt_glitch_filter_config_t filter_config = {
        .max_glitch_ns = 10,
    };
    ESP_ERROR_CHECK(pcnt_unit_set_glitch_filter(pcnt_unit, &filter_config));

    ESP_LOGI(TAG, "install pcnt channels");
    pcnt_chan_config_t chan_a_config = {
        .edge_gpio_num = PULSE_GPIO_INPUT,
        .level_gpio_num = -1,
    };
    ESP_ERROR_CHECK(pcnt_new_channel(pcnt_unit, &chan_a_config, &pcnt_chan_a));


    ESP_LOGI(TAG, "set edge and level actions for pcnt channels");
    ESP_ERROR_CHECK(pcnt_channel_set_edge_action(pcnt_chan_a, PCNT_CHANNEL_EDGE_ACTION_HOLD, PCNT_CHANNEL_EDGE_ACTION_INCREASE));

    ESP_ERROR_CHECK(pcnt_unit_add_watch_point(pcnt_unit, PULSE_PCNT_HIGH_LIMIT));

    pcnt_event_callbacks_t cbs = {
        .on_reach = pulse_pcnt_on_reach,
    };
    QueueHandle_t queue = xQueueCreate(10, sizeof(int));
    ESP_ERROR_CHECK(pcnt_unit_register_event_callbacks(pcnt_unit, &cbs, queue));

    pcnt_unit_enable(pcnt_unit);
    pcnt_unit_clear_count(pcnt_unit);
    
}

static void oneshot_timer_callback(void *arg)
{

    esp_timer_handle_t periodic_timer_handle = (esp_timer_handle_t)arg;
    pcnt_unit_stop(pcnt_unit);
    uint32_t pcount;
    pcnt_unit_get_count(pcnt_unit, &pcount);
    pulse_count += pcount;
}

static void timer_init(uint32_t time)
{
    const esp_timer_create_args_t oneshot_timer_args = {
        .callback = &oneshot_timer_callback,
        /* argument specified here will be passed to timer callback function */
        .arg = NULL,
        .name = "one-shot"};

    
    ESP_ERROR_CHECK(esp_timer_create(&oneshot_timer_args, &oneshot_timer));
    // ESP_ERROR_CHECK(esp_timer_stop(oneshot_timer));
    // ESP_ERROR_CHECK(esp_timer_start_once(oneshot_timer, time));
}

void frequency_init(void)
{
    pcnt_init();
    timer_init(PULSE_SAMPLE_TIME); //1 seconde
}

void frequency_deinit(void)
{
    timer_mes = false;
    esp_timer_delete(oneshot_timer);
    // pcnt_unit_stop(pcnt_unit);
    // pcnt_unit_disable(pcnt_unit);
    pcnt_del_channel(pcnt_chan_a);
    pcnt_del_unit(pcnt_unit);
}

uint32_t frequency_hz(void)
{
    uint32_t frequency=0;
    uint32_t count=0;
    timer_mes = true;
    pulse_count = 0;
    pcnt_unit_enable(pcnt_unit);
    pcnt_unit_clear_count(pcnt_unit);
    esp_timer_start_once(oneshot_timer, PULSE_SAMPLE_TIME);
    pcnt_unit_start(pcnt_unit);
    while (timer_mes)
    {
        vTaskDelay(10);
        count++;
        if (count > (PULSE_SAMPLE_TIME / 10000 + 2))
        {
            pcnt_unit_stop(pcnt_unit);
            pcnt_unit_disable(pcnt_unit);
            // pcnt_unit_get_count(pcnt_unit, &pulse_count);
            pulse_count = 0;
            break;
        } 
    }
    frequency = pulse_count *((float)(1000000 / PULSE_SAMPLE_TIME )* 2) ;
    pulse_count = 0;
    count = 0;
    printf("caculate frequency %ld\r\n", frequency);
    // pcnt_unit_stop(pcnt_unit);

    return frequency;
}