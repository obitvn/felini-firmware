#include <cstdio>
#include "HAL.h"
#include "stdio.h"

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/rmt_tx.h"
#include "led_strip_encoder.h"

#define RMT_LED_STRIP_RESOLUTION_HZ 10000000 // 10MHz resolution, 1 tick = 0.1us (led strip needs a high resolution)
#define RMT_LED_STRIP_GPIO_NUM 2

#define EXAMPLE_LED_NUMBERS 16
#define EXAMPLE_CHASE_SPEED_MS 1

static const char *TAG = "example";

static uint8_t led_strip_pixels[EXAMPLE_LED_NUMBERS * 3];

rmt_channel_handle_t led_chan = NULL;

rmt_tx_channel_config_t tx_chan_config = {
    .gpio_num = (gpio_num_t)RMT_LED_STRIP_GPIO_NUM,
    .clk_src = RMT_CLK_SRC_DEFAULT, // select source clock
    .resolution_hz = RMT_LED_STRIP_RESOLUTION_HZ,
    .mem_block_symbols = 128, // increase the block size can make the LED less flickering
    .trans_queue_depth = 4,  // set the number of transactions that can be pending in the background
    .flags = 0,
};

rmt_encoder_handle_t led_encoder = NULL;

led_strip_encoder_config_t led_encoder_config = {
    .resolution = RMT_LED_STRIP_RESOLUTION_HZ,
};

rmt_transmit_config_t tx_config = {
    .loop_count = 0, // no transfer loop
};

static uint8_t red = 0;
static uint8_t green = 0;
static uint8_t blue = 0;

TaskHandle_t led_strip_task_handle = NULL;

extern "C"
{

    static void led_strip_task(void *pvParameter)
    {
        // ESP_LOGI(TAG, "Create LED Strip task...................");
        while (1)
        {
            for (int i = 0; i < 3; i++)
            {
                for (int j = i; j < EXAMPLE_LED_NUMBERS; j += 3)
                {
                    led_strip_pixels[j * 3 + 0] = green;
                    led_strip_pixels[j * 3 + 1] = red;
                    led_strip_pixels[j * 3 + 2] = blue;
                }
                // printf("r %ld g %ld b %ld\r\n", info->red, info->green, info->blue);
                // Flush RGB values to LEDs
                rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config);
                vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
                memset(led_strip_pixels, 0, sizeof(led_strip_pixels));
                rmt_transmit(led_chan, led_encoder, led_strip_pixels, sizeof(led_strip_pixels), &tx_config);
                vTaskDelay(pdMS_TO_TICKS(EXAMPLE_CHASE_SPEED_MS));
            }
            vTaskDelay(5);
        }
    }
}


void HAL::LEDSTRIP_Init()
{

    ESP_LOGI(TAG, "Create RMT TX channel");
    
    rmt_new_tx_channel(&tx_chan_config, &led_chan);

    ESP_LOGI(TAG, "Install led strip encoder");
    
    rmt_new_led_strip_encoder(&led_encoder_config, &led_encoder);

    ESP_LOGI(TAG, "Enable RMT TX channel");
    rmt_enable(led_chan);

    ESP_LOGI(TAG, "Start LED rainbow chase");

    // if (led_strip_task_handle != NULL)
    // {
    //     vTaskDelete(led_strip_task_handle);
    // }
    xTaskCreate(led_strip_task, "led_strip_task", 1024 , NULL, 10, &led_strip_task_handle);
}
void HAL::LEDSTRIP_GetInfo(LEDSTRIP_Info_t *info)
{

}

void HAL::LEDSTRIP_Update(LEDSTRIP_Info_t *info)
{
    red   = info->red;
    green = info->green;
    blue  = info->blue;
}

void HAL::LEDSTRIP_Deinit()
{
    if (led_strip_task_handle != NULL)
    {
        vTaskDelete(led_strip_task_handle);
    }
    rmt_disable(led_chan);
    rmt_del_channel(led_chan);
}