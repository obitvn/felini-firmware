#include "AppLumia.h"
#include <cstdio>


using namespace Page;

AppLumia::AppLumia()
{
}

AppLumia::~AppLumia()
{
}

void AppLumia::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void AppLumia::onViewLoad()
{
    StatusBar::Appear(true);
    Model.Init();
    View.Create(root);
    AttachEvent(root);

    lv_obj_set_user_data(root, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    AppLumiaView::item_t *item_grp = ((AppLumiaView::item_t *)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(AppLumiaView::item_t); i++)
    {
        AttachEvent(item_grp[i].btn);
        AttachEvent(item_grp[i].btn_cell);
    }
}

void AppLumia::onViewDidLoad()
{
}

void AppLumia::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void AppLumia::onViewDidAppear()
{
    
}

void AppLumia::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void AppLumia::onViewDidDisappear()
{
}

void AppLumia::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void AppLumia::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void AppLumia::Update()
{

}

void AppLumia::onTimer(lv_timer_t *timer)
{

}




void AppLumia::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    AppLumia *instance = (AppLumia *)lv_obj_get_user_data(obj);

    AppLumiaView::item_t *item_grp = ((AppLumiaView::item_t *)&instance->View.ui);

    // printf("event %d\r\n", code);

    // if (obj == instance->root)
    // {
    //     if (LV_EVENT_GESTURE == code)
    //     {
    //         lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    //         if (LV_DIR_RIGHT == dir)
    //         {
    //             instance->Manager->Pop();
    //         }
    //     }
    // }

    for (int i = 0; i < sizeof(instance->View.ui) / sizeof(AppLumiaView::item_t); i++)
    {
        if ((obj == item_grp[i].btn) || (obj == item_grp[i].btn_cell))
        {
            if (code == LV_EVENT_CLICKED)
            {
                instance->Manager->Push(item_grp[i].app_src); // load page mới
            }
        }
    }
}
