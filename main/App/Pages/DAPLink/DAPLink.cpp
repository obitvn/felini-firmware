#include "DAPLink.h"
#include <cstdio>


using namespace Page;

DAPLink::DAPLink()
{
}

DAPLink::~DAPLink()
{
}

void DAPLink::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);
}

void DAPLink::onViewLoad()
{
    
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);
    AttachEvent(root);
    // AttachEvent(View.switch_cont);
    Model.DAPCommand(1); // crash
}

void DAPLink::onViewDidLoad()
{
}

void DAPLink::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void DAPLink::onViewDidAppear()
{
    
}

void DAPLink::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void DAPLink::onViewDidDisappear()
{
}

void DAPLink::onViewDidUnload()
{
    Model.DAPCommand(0);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void DAPLink::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void DAPLink::Update()
{

}

void DAPLink::onTimer(lv_timer_t *timer)
{

}

static int value = 0;

void DAPLink::enableHW(int value)
{
    Model.DAPCommand(value );
}



void DAPLink::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    DAPLink *instance = (DAPLink *)lv_obj_get_user_data(obj);

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
}
