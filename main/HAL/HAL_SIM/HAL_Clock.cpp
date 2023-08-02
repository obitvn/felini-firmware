#include "HAL.h"

#define TAG "HAL_CLOCK"
// i2c_dev_t bm8563_dev; // thread safe

void HAL::Clock_Init()
{
    // bm8563_init_desc(&bm8563_dev, 0, (gpio_num_t)21, (gpio_num_t)22);
}

void HAL::Clock_GetInfo(Clock_Info_t *info)
{
    // struct tm time;
    // bool valid;
    // // bm8563_get_time(&bm8563_dev, &time, &valid);

    // info->year = time.tm_yday;
    // info->month = time.tm_mon;
    // info->day = time.tm_mday;
    // info->week = time.tm_wday;
    // info->hour = time.tm_hour;
    // info->minute = time.tm_min;
    // info->second = time.tm_sec;
    // info->millisecond = 0;
}

void HAL::Clock_SetInfo(const Clock_Info_t *info)
{
    // struct tm time;

    // time.tm_year = info->year,     // years since 1900
    //     time.tm_mon = info->month, // months since January
    //     time.tm_mday = info->day,
    // time.tm_hour = info->hour,
    // time.tm_min = info->minute,
    // time.tm_sec = info->second,
    // time.tm_wday = 0, // days since Sunday
    //     time.tm_yday = 0,
    // time.tm_isdst = 0,

    // bm8563_set_time(&bm8563_dev, &time);
}

const char *HAL::Clock_GetWeekString(uint8_t week)
{
    const char *week_str[] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};
    return week < 7 ? week_str[week] : "";
}
