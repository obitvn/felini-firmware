#include "AppInfosView.h"

using namespace Page;

#define ITEM_HEIGHT_MIN   100
#define ITEM_PAD ((LV_VER_RES - ITEM_HEIGHT_MIN) / 2)

void AppInfosView::Create(lv_obj_t* root)
{

    lv_obj_set_style_border_width(root, 0, 0);


    lv_obj_set_style_pad_ver(root, ITEM_PAD, 0);
    lv_obj_set_style_bg_color(root, lv_color_hex(0), NULL);
    lv_obj_set_flex_flow(root, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        root,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_START,
        LV_FLEX_ALIGN_CENTER
    );


    

    Style_Init();

    /* Item Sport */
    Item_Create(
        "Pages/AnalogViewer",
        &ui.sport,
        root,
        "Analog",
        "settings_blue_png",

        "View Analog Signal\n"
        "0 - 3300mV\n"
        "View signal");

    /* Item GPS */
    Item_Create(
        "Pages/ColorWheel",
        &ui.gps,
        root,
        "Color",
        "remove_blue_png",

        "Control LED RGB\n"
        "LED WS2812\n"
        "LED FullColor\n"
        "DMX\n"
        );

    /* Item MAG */
    Item_Create(
        "Pages/HappyBirthday",
        &ui.mag,
        root,
        "Show",
        "compass",

        "Compass\n"
        "X\n"
        "Y\n"
        "Z");

    /* Item IMU */
    Item_Create(
        "Pages/IICDiscovery",
        &ui.imu,
        root,
        "I2CScan",
        "bacl_blue_png",

        "Scan Device\n"
        "Check version\n"
        "Read sensor\n");

    /* Item RTC */
    Item_Create(
        "Pages/PowerSupply",
        &ui.rtc,
        root,
        "Power",
        "list_menu_blue_png",

        "Power Supply\n"
        "Support USB PD\n"
        "Support USB PPS\n");

    /* Item Battery */
    Item_Create(
        "Pages/ServoCtrl",
        &ui.battery,
        root,
        "Servo",
        "home_blue_png",

        "Servo Testing\n"
        "PwM generator\n"
        "V1.24");

    /* Item Storage */
    Item_Create(
        "Pages/HappyBirthday",
        &ui.storage,
        root,
        "Pulse",
        "storage",
        "Pulse Generator\n"
        "0 - 40 Mhz\n"
        "Square pulse\n"
        "PWM");

    /* Item System */
    Item_Create(
        "Pages/ColorWheel",
        &ui.system,
        root,
        "DAPLink",
        "pause",
        "DAP Link debugger\n"
        "V2.2.3\n"
        "USB UART\n");

    Group_Init();
}

void AppInfosView::Group_Init()
{
    lv_group_t* group = lv_group_get_default();
    lv_group_set_wrap(group, true);
    lv_group_set_focus_cb(group, onFocus);

    item_t* item_grp = ((item_t*)&ui);

    /* Reverse adding to group makes encoder operation more comfortable */
    for (int i = sizeof(ui) / sizeof(item_t) - 1; i >= 0; i--)
    {
        lv_group_add_obj(group, item_grp[i].icon);
    }

    lv_group_focus_obj(item_grp[0].icon);
}

void AppInfosView::Delete()
{
    lv_group_set_focus_cb(lv_group_get_default(), nullptr);
    Style_Reset();
}

void AppInfosView::SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en)
{
    lv_coord_t scroll_y = lv_obj_get_scroll_y(obj);
    lv_coord_t diff = -y + scroll_y;

    lv_obj_scroll_by(obj, 0, diff, en);
}

void AppInfosView::onFocus(lv_group_t* g)
{
    lv_obj_t* icon = lv_group_get_focused(g);
    lv_obj_t* cont = lv_obj_get_parent(icon);
    lv_coord_t y = lv_obj_get_y(cont);
    lv_obj_scroll_to_y(lv_obj_get_parent(cont), y, LV_ANIM_ON);
}

void AppInfosView::Style_Init()
{
    lv_style_init(&style.icon);
    lv_style_set_width(&style.icon, 260);
    lv_style_set_bg_color(&style.icon, lv_color_black());
    lv_style_set_bg_opa(&style.icon, LV_OPA_COVER);
    lv_style_set_text_font(&style.icon, ResourcePool::GetFont("SFCompact22bpp8"));
    lv_style_set_text_color(&style.icon, lv_color_white());

    lv_style_init(&style.focus);
    lv_style_set_width(&style.focus, 70);
    lv_style_set_border_side(&style.focus, LV_BORDER_SIDE_RIGHT);
    lv_style_set_border_width(&style.focus, 3);
    lv_style_set_border_color(&style.focus, lv_color_hex(0x4682B4));

    static const lv_style_prop_t style_prop[] =
    {
        LV_STYLE_WIDTH,
        LV_STYLE_PROP_INV
    };

    static lv_style_transition_dsc_t trans;
    lv_style_transition_dsc_init(
        &trans,
        style_prop,
        lv_anim_path_overshoot,
        200,
        0,
        nullptr
    );
    lv_style_set_transition(&style.focus, &trans);
    lv_style_set_transition(&style.icon, &trans);

    lv_style_init(&style.info);
    lv_style_set_text_font(&style.info, ResourcePool::GetFont("SFCompact22bpp8"));
    lv_style_set_text_color(&style.info, lv_color_hex(0x999999));

    lv_style_init(&style.data);
    lv_style_set_text_font(&style.data, ResourcePool::GetFont("SFCompact22bpp8"));
    lv_style_set_text_color(&style.data, lv_color_white());
}

void AppInfosView::Style_Reset()
{
    lv_style_reset(&style.icon);
    lv_style_reset(&style.info);
    lv_style_reset(&style.data);
    lv_style_reset(&style.focus);
}

void AppInfosView::Item_Create(
    const char *app_src,
    item_t * item,
    lv_obj_t *par,
    const char *name,
    const char *img_src,
    const char *infos)
{
    item->app_src = app_src;
    lv_obj_t* cont = lv_obj_create(par);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, 220);

    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    item->cont = cont;

    /* icon */
    lv_obj_t* icon = lv_obj_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(icon);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_style(icon, &style.icon, 0);
    lv_obj_add_style(icon, &style.focus, LV_STATE_FOCUSED);
    lv_obj_set_style_align(icon, LV_ALIGN_LEFT_MID, 0);

    lv_obj_set_flex_flow(icon, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        icon,
        LV_FLEX_ALIGN_SPACE_AROUND,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER
    );

    lv_obj_t* img = lv_img_create(icon);
    lv_obj_enable_style_refresh(false);
    lv_img_set_src(img, ResourcePool::GetImage(img_src));

    lv_obj_t* label = lv_label_create(icon);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, name);
    item->icon = icon;

    /* infos */
    label = lv_label_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, infos);
    lv_obj_add_style(label, &style.info, 0);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 75, 0);
    item->labelInfo = label;

    /* datas */
    label = lv_label_create(cont);
    // lv_obj_enable_style_refresh(false);
    // lv_label_set_text(label, "-");
    // lv_obj_add_style(label, &style.data, 0);
    // lv_obj_align(label, LV_ALIGN_CENTER, 60, 0);
    item->labelData = label;

    lv_obj_move_foreground(icon);
    lv_obj_enable_style_refresh(true);

    /* get real max height */
    lv_obj_update_layout(item->labelInfo);
    lv_coord_t height = lv_obj_get_height(item->labelInfo);
    height = LV_MAX(height, ITEM_HEIGHT_MIN);
    lv_obj_set_height(cont, height);
    lv_obj_set_height(icon, height);
}

void AppInfosView::SetSport(
    float trip,
    const char* time,
    float maxSpd
)
{
    lv_label_set_text_fmt(
        ui.sport.labelData,
        "%0.2fkm\n"
        "%s\n"
        "%0.1fkm/h",
        trip,
        time,
        maxSpd
    );
}

void AppInfosView::SetGPS(
    float lat,
    float lng,
    float alt,
    const char* utc,
    float course,
    float speed
)
{
    lv_label_set_text_fmt(
        ui.gps.labelData,
        "%0.6f\n"
        "%0.6f\n"
        "%0.2fm\n"
        "%s\n"
        "%0.1f deg\n"
        "%0.1fkm/h",
        lat,
        lng,
        alt,
        utc,
        course,
        speed
    );
}

void AppInfosView::SetMAG(
    float dir,
    int x,
    int y,
    int z
)
{
    lv_label_set_text_fmt(
        ui.mag.labelData,
        "%0.1f deg\n"
        "%d\n"
        "%d\n"
        "%d",
        dir,
        x,
        y,
        z
    );
}

void AppInfosView::SetIMU(
    int step,
    const char* info
)
{
    lv_label_set_text_fmt(
        ui.imu.labelData,
        "%d\n"
        "%s",
        step,
        info
    );
}

void AppInfosView::SetRTC(
    const char* dateTime
)
{
    lv_label_set_text(
        ui.rtc.labelData,
        dateTime
    );
}

void AppInfosView::SetBattery(
    int usage,
    float voltage,
    const char* state
)
{
    lv_label_set_text_fmt(
        ui.battery.labelData,
        "%d%%\n"
        "%0.2fV\n"
        "%s",
        usage,
        voltage,
        state
    );
}

void AppInfosView::SetStorage(
    const char* detect,
    const char* size,
    const char* type,
    const char* version
)
{
    lv_label_set_text_fmt(
        ui.storage.labelData,
        "%s\n"
        "%s\n"
        "%s\n"
        "%s",
        detect,
        size,
        type,
        version
    );
}

void AppInfosView::SetSystem(
    const char* firmVer,
    const char* authorName,
    const char* lvglVer,
    const char* bootTime,
    const char* compilerName,
    const char* bulidTime
)
{
    lv_label_set_text_fmt(
        ui.system.labelData,
        "%s\n"
        "%s\n"
        "%s\n"
        "%s\n"
        "%s\n"
        "%s",
        firmVer,
        authorName,
        lvglVer,
        bootTime,
        compilerName,
        bulidTime
    );
}
