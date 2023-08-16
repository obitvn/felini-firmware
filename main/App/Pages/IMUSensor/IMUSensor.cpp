#include "IMUSensor.h"
#include <cstdio>


using namespace Page;

IMUSensor::IMUSensor()
{
}

IMUSensor::~IMUSensor()
{
}

void IMUSensor::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void IMUSensor::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(root);
}

void IMUSensor::onViewDidLoad()
{
}

void IMUSensor::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void IMUSensor::onViewDidAppear()
{
    
}

void IMUSensor::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void IMUSensor::onViewDidDisappear()
{
}

void IMUSensor::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void IMUSensor::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void IMUSensor::Update()
{

}

void IMUSensor::onTimer(lv_timer_t *timer)
{

}




void IMUSensor::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    IMUSensor *instance = (IMUSensor *)lv_obj_get_user_data(obj);

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
