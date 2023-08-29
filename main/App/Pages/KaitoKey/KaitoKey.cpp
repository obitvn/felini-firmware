#include "KaitoKey.h"
#include <cstdio>


using namespace Page;

KaitoKey::KaitoKey()
{
}

KaitoKey::~KaitoKey()
{
}

void KaitoKey::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void KaitoKey::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(root);
}

void KaitoKey::onViewDidLoad()
{
}

void KaitoKey::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void KaitoKey::onViewDidAppear()
{
    
}

void KaitoKey::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void KaitoKey::onViewDidDisappear()
{
}

void KaitoKey::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void KaitoKey::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void KaitoKey::Update()
{

}

void KaitoKey::onTimer(lv_timer_t *timer)
{

}




void KaitoKey::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    KaitoKey *instance = (KaitoKey *)lv_obj_get_user_data(obj);

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
