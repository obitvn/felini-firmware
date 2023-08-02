#include "HAL.h"
#include <time.h>
#include <stdio.h>

#define TAG "HAL_CLOCK"
// i2c_dev_t bm8563_dev; // thread safe

void HAL::Clock_Init()
{
    // bm8563_init_desc(&bm8563_dev, 0, (gpio_num_t)21, (gpio_num_t)22);
}

void HAL::Clock_GetInfo(Clock_Info_t *info)
{
    struct tm *t;
    time_t tt;
    time(&tt);
    t = localtime(&tt);

    info->year = t->tm_year + 1900;
    info->month = t->tm_mon + 1;
    info->day = t->tm_mday;
    info->week = t->tm_wday;
    info->hour = t->tm_hour;
    info->minute = t->tm_min;
    info->second = t->tm_sec;
    info->millisecond = t->tm_sec;
}

void HAL::Clock_SetInfo(const Clock_Info_t *info)
{
    printf(
        "\nClock set: %04d-%02d-%02d %02d:%02d:%02d\n",
        info->year,
        info->month,
        info->day,
        info->hour,
        info->minute,
        info->second);
}

const char *HAL::Clock_GetWeekString(uint8_t week)
{
    const char *week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
