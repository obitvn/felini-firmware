#include "Resource/ResourcePool.h"
#include "Utils/PageManager/PageManager.h"
#include "Utils/PageManager/ResourceManager.h"

static ResourceManager Font_;
static ResourceManager Image_;

extern "C"
{
#define IMPORT_FONT(name)                               \
    do                                                  \
    {                                                   \
        LV_FONT_DECLARE(font_##name)                    \
        Font_.AddResource(#name, (void *)&font_##name); \
    } while (0)

#define IMPORT_IMG(name)                                    \
    do                                                      \
    {                                                       \
        LV_IMG_DECLARE(img_src_##name)                      \
        Image_.AddResource(#name, (void *)&img_src_##name); \
    } while (0)

#define IMPORT_IMG_WEATHER(name)                                    \
    do                                                              \
    {                                                               \
        LV_IMG_DECLARE(img_src_weather_##name)                      \
        Image_.AddResource(#name, (void *)&img_src_weather_##name); \
    } while (0)

    static void Resource_Init()
    {
        /* Import Fonts */
        IMPORT_FONT(alibabasans_medium_36);
        IMPORT_FONT(alibabasans_regular_13);
        IMPORT_FONT(alibabasans_regular_17);
        IMPORT_FONT(alibabasans_regular_26);
        IMPORT_FONT(alibabasans_regular_32);
        IMPORT_FONT(alibabasans_regular_48);
        IMPORT_FONT(alibabasans_regular_60);

        /* Import Images */
        IMPORT_IMG(alarm);
        IMPORT_IMG(battery_red);
        IMPORT_IMG(battery);
        IMPORT_IMG(location);
        IMPORT_IMG(message);
        IMPORT_IMG(origin_point);
        IMPORT_IMG(pause);
        IMPORT_IMG(sd_card);
        IMPORT_IMG(storage);
        IMPORT_IMG(wifi_connect);

        IMPORT_IMG(back_blue_png);
        IMPORT_IMG(catb_png);
        IMPORT_IMG(home_blue_png);
        IMPORT_IMG(list_menu_blue_png);
        IMPORT_IMG(remove_blue_png);
        IMPORT_IMG(settings_blue_png);

    }

} /* extern "C" */

void ResourcePool::Init()
{
    Resource_Init();
    Font_.SetDefault((void *)&lv_font_montserrat_14);
}

lv_font_t *ResourcePool::GetFont(const char *name)
{
    return (lv_font_t *)Font_.GetResource(name);
}
const void *ResourcePool::GetImage(const char *name)
{
    return Image_.GetResource(name);
}
