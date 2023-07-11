#pragma once
#include <stdint.h>
#include "gpio.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif

#ifndef __WEAK
#define __WEAK __attribute__((weak))
#endif

#define PIN_SWCLK_TCK GPIO_NUM_5
#define PIN_SWDIO_TMS GPIO_NUM_6
#define PIN_TDI GPIO_NUM_7
#define PIN_TDO GPIO_NUM_8
#define PIN_nRESET GPIO_NUM_9
#define LED_CONNECTED GPIO_NUM_10
#define LED_RUNNING GPIO_NUM_11

#define DAP_CPU_CLOCK 0U

void dap_platform_init(void);
void dap_gpio_init(void);

static inline uint32_t dap_get_time_stamp(void)
{
    return (uint32_t)xTaskGetTickCount();
}
