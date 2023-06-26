#include <cstdio>
#include "HAL.h"
#ifdef __cplusplus
extern "C"
{
#endif
// #include "seniverse.h"
#ifdef __cplusplus
}
#endif

void HAL::Weather_Init()
{
}

void HAL::Weather_GetInfo(Weather_Info_t *info)
{
    // weather_now weather_now_info;
    // int count = 0;
    // if (seniverse_get_weather(SENIVERSE_WEATHER_NOW, (char *)CONFIG_PLACE_NAME, &weather_now_info, &count, 0, 0) == 0) {
    //     snprintf(info->summary, 16, "%s", weather_now_info.items[0].summary);
    //     snprintf(info->last_update, 128, "%s", weather_now_info.common.last_update);
    //     info->temperature = weather_now_info.items[0].temperature;
    //     info->code = weather_now_info.items[0].code;
    // } else {
    //     ESP_LOGE("HAL::Weather", "seniverse_get_weather error");
    //     snprintf(info->summary, 16, "%s", "Error");
    //     snprintf(info->last_update, 128, "%s", "Get error,will try again after 10s.");
    //     info->temperature = 0.0f;
    //     info->code = 99;
    // }
}
