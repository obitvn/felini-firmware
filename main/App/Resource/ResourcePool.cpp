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

        IMPORT_IMG_WEATHER(0);
        IMPORT_IMG_WEATHER(1);
        IMPORT_IMG_WEATHER(2);
        IMPORT_IMG_WEATHER(3);
        IMPORT_IMG_WEATHER(4);
        IMPORT_IMG_WEATHER(5);
        IMPORT_IMG_WEATHER(6);
        IMPORT_IMG_WEATHER(7);
        IMPORT_IMG_WEATHER(8);
        IMPORT_IMG_WEATHER(9);
        IMPORT_IMG_WEATHER(10);
        IMPORT_IMG_WEATHER(11);
        IMPORT_IMG_WEATHER(12);
        IMPORT_IMG_WEATHER(13);
        IMPORT_IMG_WEATHER(14);
        IMPORT_IMG_WEATHER(15);
        IMPORT_IMG_WEATHER(16);
        IMPORT_IMG_WEATHER(17);
        IMPORT_IMG_WEATHER(18);
        IMPORT_IMG_WEATHER(19);
        IMPORT_IMG_WEATHER(20);
        IMPORT_IMG_WEATHER(21);
        IMPORT_IMG_WEATHER(22);
        IMPORT_IMG_WEATHER(23);
        IMPORT_IMG_WEATHER(24);
        IMPORT_IMG_WEATHER(25);
        IMPORT_IMG_WEATHER(26);
        IMPORT_IMG_WEATHER(27);
        IMPORT_IMG_WEATHER(28);
        IMPORT_IMG_WEATHER(29);
        IMPORT_IMG_WEATHER(30);
        IMPORT_IMG_WEATHER(31);
        IMPORT_IMG_WEATHER(32);
        IMPORT_IMG_WEATHER(33);
        IMPORT_IMG_WEATHER(34);
        IMPORT_IMG_WEATHER(35);
        IMPORT_IMG_WEATHER(36);
        IMPORT_IMG_WEATHER(37);
        IMPORT_IMG_WEATHER(38);
        IMPORT_IMG_WEATHER(99);

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
