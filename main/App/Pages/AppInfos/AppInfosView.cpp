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
        &ui.analog,
        root,
        "ADC",
        "analog",

        "View Analog Signal\n"
        "0 - 3300mV\n"
        "View signal");

    /* Item GPS */
    Item_Create(
        "Pages/ColorWheel",
        &ui.ledcolor,
        root,
        "LED",
        "color",

        "Control LED RGB\n"
        "LED WS2812\n"
        "LED FullColor\n"
        "DMX\n"
        );

    /* Item MAG */
    Item_Create(
        "Pages/IICDiscovery",
        &ui.timekeeper,
        root,
        "Interval",
        "clock",

        "Signal duration \n"
        "Get pulse\n"
        "View delay\n"
        "v1.2.2");

    /* Item IMU */
    Item_Create(
        "Pages/IICDiscovery",
        &ui.i2cscan,
        root,
        "I2C",
        "i2cnetwork",

        "Scan Device\n"
        "Check version\n"
        "Read sensor\n");

    /* Item RTC */
    Item_Create(
        "Pages/PowerSupply",
        &ui.powerpd,
        root,
        "Power",
        "power",

        "Power Supply\n"
        "Support USB PD\n"
        "Support USB PPS\n");

    /* Item Battery */
    Item_Create(
        "Pages/ServoCtrl",
        &ui.ccpmservo,
        root,
        "Servo",
        "volang",

        "CCPM Servo / ESC\n"
        "Consistency Master\n"
        "V1.0.0");

    /* Item Storage */
    Item_Create(
        "Pages/HappyBirthday",
        &ui.uartter,
        root,
        "UART",
        "updown",

        "Pulse Generator\n"
        "0 - 40 Mhz\n"
        "Square pulse\n"
        "PWM");

    /* Item System */
    Item_Create(
        "Pages/DAPLink",
        &ui.daplink,
        root,
        "DAPLink",
        "link",
        
        "DAP Link debugger\n"
        "V2.2.3\n"
        "USB UART\n");

    /* Item System */
    Item_Create(
        "Pages/DAPLink",
        &ui.usbcanbus,
        root,
        "CAN Bus",
        "canbus",

        "USB to CAN\n"
        "CandleLight\n"
        "V2.2.3\n"
        "Socket CAN\n");

    /* Item System */
    Item_Create(
        "Pages/DAPLink",
        &ui.frequency,
        root,
        "Hertz",
        "chip",

        "Measure Frequency\n"
        "Cycle\n"
        "V2.2.3\n"
        "Frequency counter\n");

    /* Item System */
    Item_Create(
        "Pages/DAPLink",
        &ui.imu,
        root,
        "IMU",
        "box3d",

        "IMU Sensor\n"
        "3d Viewer\n"
        "V2.2.3\n");

    Group_Init();
}



void AppInfosView::Group_Init()
{
    lv_group_t *group = lv_group_get_default();
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


void AppInfosView::SetFocus(int dir)
{
    lv_group_t *group = lv_group_get_default();
    if(dir > 0)
    {
        lv_group_focus_next(group);
    }
    else
    {
        lv_group_focus_prev(group);
    }
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
    lv_style_set_width(&style.focus, 95);
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
        250,
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
    lv_obj_set_width(cont, 260);

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
    lv_obj_set_style_text_color(label, lv_color_hex(0x4682B4), 0);
    lv_label_set_text(label, name);
    item->icon = icon;

    /* infos */
    label = lv_label_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, infos);
    lv_obj_add_style(label, &style.info, 0);
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 115, 0);
    item->labelInfo = label;

    // /* datas */
    // label = lv_label_create(cont);
    // lv_obj_enable_style_refresh(false);
    // lv_label_set_text(label, "-");
    // lv_obj_add_style(label, &style.data, 0);
    // lv_obj_align(label, LV_ALIGN_CENTER, 60, 0);
    // item->labelData = label;

    lv_obj_move_foreground(icon);
    lv_obj_enable_style_refresh(true);

    /* get real max height */
    lv_obj_update_layout(item->labelInfo);
    lv_coord_t height = lv_obj_get_height(item->labelInfo);
    height = LV_MAX(height, ITEM_HEIGHT_MIN);
    lv_obj_set_height(cont, height);
    lv_obj_set_height(icon, height);
}
