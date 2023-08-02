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

        IMPORT_IMG(analog);
        IMPORT_IMG(power);
        IMPORT_IMG(box3d);
        IMPORT_IMG(canbus);
        IMPORT_IMG(chip);
        IMPORT_IMG(clock);
        IMPORT_IMG(color);
        IMPORT_IMG(finding);
        IMPORT_IMG(folder);
        IMPORT_IMG(i2cnetwork);
        IMPORT_IMG(i2cscan);
        IMPORT_IMG(info);
        IMPORT_IMG(link);
        IMPORT_IMG(scan);
        IMPORT_IMG(servo);
        IMPORT_IMG(setting);
        IMPORT_IMG(terminal);
        IMPORT_IMG(updown);
        IMPORT_IMG(volang);
        IMPORT_IMG(pinmap_servo);
        IMPORT_IMG(catb);
        IMPORT_IMG(dap_bug);
        IMPORT_IMG(dap_connected);
        IMPORT_IMG(dap_disconnect);
        IMPORT_IMG(down_dap);
        IMPORT_IMG(pin_daplink);

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
