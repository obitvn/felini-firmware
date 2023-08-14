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
        AttachEvent(item_grp[i].cont);
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
 
}

void AppInfos::onTimerUpdate(lv_timer_t* timer)
{
    AppInfos* instance = (AppInfos*)timer->user_data;

    instance->Update();
}

void AppInfos::onEvent(lv_event_t* event)
{
    AppInfos* instance = (AppInfos*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

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

    AppInfosView::item_t *item_grp = ((AppInfosView::item_t *)&instance->View.ui);
    
    for (int i = 0; i < sizeof(instance->View.ui) / sizeof(AppInfosView::item_t); i++)
    {
        if (obj == item_grp[i].cont) //
        {
            if (code == LV_EVENT_PRESSED)
            {
                // printf("pressing at button %d app_src %s\r\n", i, item_grp[i].app_src);
                // instance->Manager->Pop(); //đóng page và quay về page trước đó
                instance->Manager->Push(item_grp[i].app_src); // load page mới, đang lỗi chưa load được
            }
        }
    }

    

    if (code == LV_EVENT_GESTURE)
    {
        printf("geasure\r\n");
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        printf("Dir: %d\n", dir);
    }

    if (obj == instance->root)
    {
        if (code == LV_EVENT_LEAVE)
        {
            // printf("LV_EVENT_LEAVE\r\n");
            instance->Manager->Pop();
        }
    }
}
