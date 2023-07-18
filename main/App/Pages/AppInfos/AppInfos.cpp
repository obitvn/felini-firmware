#include "AppInfos.h"
#include <cstdio>

using namespace Page;

AppInfos::AppInfos()
{
}

AppInfos::~AppInfos()
{

}

void AppInfos::onCustomAttrConfig()
{
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void AppInfos::onViewLoad()
{

    Model.Init();
    View.Create(root);
    AttachEvent(root);

    AppInfosView::item_t* item_grp = ((AppInfosView::item_t*)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(AppInfosView::item_t); i++)
    {
        AttachEvent(item_grp[i].icon);
    }
}

void AppInfos::onViewDidLoad()
{

}

void AppInfos::onViewWillAppear()
{

    lv_obj_set_style_bg_color(root, lv_color_hex(0), NULL);
    Model.SetStatusBarStyle(DataProc::STATUS_BAR_STYLE_BLACK);
    timer = lv_timer_create(onTimerUpdate, 1000, this);
    lv_timer_ready(timer);

    View.SetScrollToY(root, -LV_VER_RES, LV_ANIM_OFF);
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 100);
    lv_obj_fade_in(root, 300, 0);
}

void AppInfos::onViewDidAppear()
{
    lv_group_t* group = lv_group_get_default();
    LV_ASSERT_NULL(group);
    View.onFocus(group);
}

void AppInfos::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void AppInfos::onViewDidDisappear()
{
    lv_timer_del(timer);
}

void AppInfos::onViewUnload()
{
    View.Delete();
    Model.Deinit();
}

void AppInfos::onViewDidUnload()
{

}

void AppInfos::AttachEvent(lv_obj_t* obj)
{
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void AppInfos::Update()
{
    const char buf[64]="buf test 12\r\n";

    /* Sport */
    float trip;
    float maxSpd;
    // Model.GetSportInfo(&trip, buf, sizeof(buf), &maxSpd);
    // View.SetSport(98.21, buf, 32.8);

    /* GPS */
    float lat;
    float lng;
    float alt;
    float course;
    float speed;
    // Model.GetGPSInfo(&lat, &lng, &alt, buf, sizeof(buf), &course, &speed);
    // View.SetGPS(23.67, 78.21, 92.54, buf, 2.86, 72.4);

    /* MAG */
    float dir;
    int x;
    int y;
    int z;
    // Model.GetMAGInfo(&dir, &x, &y, &z);
    // View.SetMAG(1.2, 254, 866, 421);

    /* IMU */
    int steps;
    // Model.GetIMUInfo(&steps, buf, sizeof(buf));
    // View.SetIMU(1241, buf);

    /* RTC */
    // Model.GetRTCInfo(buf, sizeof(buf));
    // View.SetRTC(buf);

    /* Power */
    int usage;
    float voltage;
    // Model.GetBatteryInfo(&usage, &voltage, buf, sizeof(buf));
    // View.SetBattery(78, 3.763, buf);

    /* Storage */
    bool detect;
    const char* type = "-";
    // Model.GetStorageInfo(&detect, &type, buf, sizeof(buf));
    // View.SetStorage(
    //     "OK",
    //     buf,
    //     type,
    //     "tes"
    // );

    /* System */
    // DataProc::MakeTimeString(lv_tick_get(), buf, sizeof(buf));
    // View.SetSystem(
    //     "1.3.4" " " "8ab3",
    //     "tienthinh",
    //     "8xxx",
    //     buf,
    //     "ninja esp",
    //     "200723"
    // );
}

void AppInfos::onTimerUpdate(lv_timer_t* timer)
{
    AppInfos* instance = (AppInfos*)timer->user_data;

    instance->Update();
}

void AppInfos::onEvent(lv_event_t* event)
{
    // AppInfos* instance = (AppInfos*)lv_event_get_user_data(event);
    // LV_ASSERT_NULL(instance);

    // lv_obj_t* obj = lv_event_get_current_target(event);
    // lv_event_code_t code = lv_event_get_code(event);

    // if (code == LV_EVENT_PRESSED)
    // {
    //     if (lv_obj_has_state(obj, LV_STATE_FOCUSED))
    //     {
    //         // instance->Manager->Pop();
    //         printf("LV_STATE_FOCUSED\r\n");
    //     }
    // }

    // if (obj == instance->root)
    // {
    //     if (code == LV_EVENT_LEAVE)
    //     {
    //         printf("LV_EVENT_LEAVE\r\n");
    //         // instance->Manager->Pop();
    //     }
    // }
}
