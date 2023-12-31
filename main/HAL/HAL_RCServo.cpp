#include <cstdio>
#include "HAL.h"
#include "stdio.h"

//esp32-s3
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/mcpwm_prelude.h"
#include "driver/ledc.h"

#include "driver/rmt_tx.h"
#include "musical_score_encoder.h"
#include <string.h>

static const char *TAG = "example";

// Please consult the datasheet of your servo before changing the following parameters
#define SERVO_MIN_PULSEWIDTH_US 500  // Minimum pulse width in microsecond
#define SERVO_MAX_PULSEWIDTH_US 2500 // Maximum pulse width in microsecond
#define SERVO_MIN_DEGREE -90           // Minimum angle
#define SERVO_MAX_DEGREE 90         // Maximum angle

#define SERVO_PULSE_GPIO 2                   // GPIO connects to the PWM signal line
#define SERVO_TIMEBASE_RESOLUTION_HZ 1000000 // 1MHz, 1us per tick
#define SERVO_TIMEBASE_PERIOD 20000          // 20000 ticks, 20ms

mcpwm_timer_handle_t timer = NULL;
mcpwm_cmpr_handle_t comparator = NULL;
mcpwm_oper_handle_t oper = NULL;
mcpwm_gen_handle_t generator = NULL;

bool freq_gen = false;
static bool set_freq = false;

static inline uint32_t example_angle_to_compare(int angle)
{
    return (angle - SERVO_MIN_DEGREE) * (SERVO_MAX_PULSEWIDTH_US - SERVO_MIN_PULSEWIDTH_US) / (SERVO_MAX_DEGREE - SERVO_MIN_DEGREE) + SERVO_MIN_PULSEWIDTH_US;
}

/* RCServo*/
void HAL::RCServo_Init()
{
    
    ESP_LOGI(TAG, "Create timer and operator");

    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = SERVO_TIMEBASE_RESOLUTION_HZ,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
        .period_ticks = SERVO_TIMEBASE_PERIOD,

    };
    ESP_ERROR_CHECK(mcpwm_new_timer(&timer_config, &timer));

    
    mcpwm_operator_config_t operator_config = {
        .group_id = 0, // operator must be in the same group to the timer
    };
    ESP_ERROR_CHECK(mcpwm_new_operator(&operator_config, &oper));

    ESP_LOGI(TAG, "Connect timer and operator");
    ESP_ERROR_CHECK(mcpwm_operator_connect_timer(oper, timer));

    ESP_LOGI(TAG, "Create comparator and generator from the operator");
    // mcpwm_cmpr_handle_t comparator = NULL;
    mcpwm_comparator_config_t comparator_config = {
        .flags = {
            .update_cmp_on_tez = true,
            .update_cmp_on_tep = false,
            .update_cmp_on_sync = false
            }
    };
    ESP_ERROR_CHECK(mcpwm_new_comparator(oper, &comparator_config, &comparator));

    
    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = SERVO_PULSE_GPIO,
    };
    ESP_ERROR_CHECK(mcpwm_new_generator(oper, &generator_config, &generator));

    // set the initial compare value, so that the servo will spin to the center position
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(0)));

    ESP_LOGI(TAG, "Set generator action on timer and compare event");
    // go high on counter empty
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_timer_event(generator,
                                                              MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH)));
    // go low on compare threshold
    ESP_ERROR_CHECK(mcpwm_generator_set_action_on_compare_event(generator,
                                                                MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW)));

    ESP_LOGI(TAG, "Enable and start timer");
    ESP_ERROR_CHECK(mcpwm_timer_enable(timer));
    ESP_ERROR_CHECK(mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP));

    // int angle = 0;
    // int step = 2;
    set_freq = false;
}
void HAL::RCServo_GetInfo(RCServo_Info_t *info)
{

}


#define RMT_BUZZER_RESOLUTION_HZ 1000000 // 1MHz resolution



void HAL::RCServo_SetFreq(RCServo_Info_t *info)
{
    freq_gen = true;


    printf("set freq %ld, duty %d\n", info->frequency, info->duty);

    if(info->frequency <1000) info->frequency = 2000;
    if(info->duty < 0) info->duty = 50 ;


    uint32_t duty_res = 16384 * (info->duty/100);

    // // Prepare and then apply the LEDC PWM timer configuration
    // ledc_timer_config_t ledc_timer = {
    //     .speed_mode = LEDC_LOW_SPEED_MODE,
    //     .duty_resolution = LEDC_TIMER_14_BIT,
    //     .timer_num = LEDC_TIMER_0,
    //     .freq_hz = info->frequency, // Set output frequency
    //     .clk_cfg = LEDC_AUTO_CLK};
    // ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // // Prepare and then apply the LEDC PWM channel configuration
    // ledc_channel_config_t ledc_channel = {
    //     .gpio_num = SERVO_PULSE_GPIO,
    //     .speed_mode = LEDC_LOW_SPEED_MODE,
    //     .channel = LEDC_CHANNEL_0,
    //     .intr_type = LEDC_INTR_DISABLE,
    //     .timer_sel = LEDC_TIMER_0,
    //     .duty = info->duty, // Set duty to 0%
    //     .hpoint = 0};
    // ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    /**
     * @brief Musical Score: Beethoven's Ode to joy
     */


    static buzzer_musical_score_t score;

    ESP_LOGI(TAG, "Create RMT TX channel");
    rmt_channel_handle_t buzzer_chan = NULL;
    rmt_tx_channel_config_t tx_chan_config = {
        .gpio_num = (gpio_num_t)1,

        .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
        .resolution_hz = RMT_BUZZER_RESOLUTION_HZ,

        .mem_block_symbols = 64,
        .trans_queue_depth = 10, // set the maximum number of transactions that can pend in the background
    };
    

    ESP_LOGI(TAG, "Install musical score encoder");
    rmt_encoder_handle_t score_encoder = NULL;
    musical_score_encoder_config_t encoder_config = {
        .resolution = RMT_BUZZER_RESOLUTION_HZ};



    ESP_LOGI(TAG, "Enable RMT TX channel");

    if (set_freq)
    {
        rmt_del_channel(buzzer_chan);
    }

    ESP_ERROR_CHECK(rmt_new_tx_channel(&tx_chan_config, &buzzer_chan));
    ESP_ERROR_CHECK(rmt_new_musical_score_encoder(&encoder_config, &score_encoder));
    ESP_ERROR_CHECK(rmt_enable(buzzer_chan));
        


    ESP_LOGI(TAG, "Playing Beethoven's Ode to joy...");

    score.freq_hz =info->frequency;
    score.duration_ms = 0;


    rmt_transmit_config_t tx_config = {
            .loop_count = -1,
        };


    ESP_ERROR_CHECK(rmt_transmit(buzzer_chan, score_encoder, &score, sizeof(buzzer_musical_score_t), &tx_config));

    set_freq = true;
}

void HAL::RCServo_Update(RCServo_Info_t *info)
{

    ESP_LOGI(TAG, "Angle of rotation: %d", info->angle-90);
    ESP_ERROR_CHECK(mcpwm_comparator_set_compare_value(comparator, example_angle_to_compare(info->angle-90)));
}

void HAL::RCServo_Deinit()
{
    ESP_LOGI(TAG, "Deinit timer servo");
    mcpwm_timer_disable(timer);
    
    mcpwm_del_comparator(comparator);
    mcpwm_del_generator(generator);
    mcpwm_del_operator(oper);
    mcpwm_del_timer(timer);
}