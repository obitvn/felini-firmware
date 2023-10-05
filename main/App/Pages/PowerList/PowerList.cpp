#include "PowerList.h"
#include <cstdio>


using namespace Page;

PowerList::PowerList()
{
}

PowerList::~PowerList()
{
}

void PowerList::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void PowerList::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);
    AttachEvent(root);

    lv_obj_set_user_data(root, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    PowerListView::item_t *item_grp = ((PowerListView::item_t *)&View.ui);

    for (int i = 0; i < sizeof(View.ui) / sizeof(PowerListView::item_t); i++)
    {
        AttachEvent(item_grp[i].btn_cell);
    }
}

void PowerList::onViewDidLoad()
{
}

void PowerList::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void PowerList::onViewDidAppear()
{
    
}

void PowerList::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void PowerList::onViewDidDisappear()
{
}

void PowerList::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void PowerList::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void PowerList::Update()
{

}

void PowerList::onTimer(lv_timer_t *timer)
{

}




void PowerList::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    PowerList *instance = (PowerList *)lv_obj_get_user_data(obj);

    PowerListView::item_t *item_grp = ((PowerListView::item_t *)&instance->View.ui);

    if (obj == instance->root)
    {
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_RIGHT == dir)
            {
                instance->Manager->Pop();
            }
        }
    }

    for (int i = 0; i < sizeof(instance->View.ui) / sizeof(PowerListView::item_t); i++)
    {
        if ((obj == item_grp[i].btn) || (obj == item_grp[i].btn_cell))
        {
            if (code == LV_EVENT_CLICKED)
            {
                // instance->Manager->Push(item_grp[i].app_src); // load page mới
            }
        }
    }
}
