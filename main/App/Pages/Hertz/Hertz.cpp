#include "Hertz.h"
#include <cstdio>


using namespace Page;

uint32_t sfreq=0;
uint8_t sduty=0;

Hertz::Hertz()
{
}

Hertz::~Hertz()
{
}

void Hertz::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void Hertz::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    sfreq = 1000;
    sduty = 50;

    lv_obj_set_user_data(root, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    HertzView::item_t *item_grp = ((HertzView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(HertzView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
}

void Hertz::onViewDidLoad()
{
}

void Hertz::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void Hertz::onViewDidAppear()
{
    
}

void Hertz::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void Hertz::onViewDidDisappear()
{
}

void Hertz::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void Hertz::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void Hertz::Update()
{

}

void Hertz::onTimer(lv_timer_t *timer)
{

}




void Hertz::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    Hertz *instance = (Hertz *)lv_obj_get_user_data(obj);



   

    if(obj == instance->View.ui.frequency.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            sfreq = lv_spinbox_get_value(obj);
            instance->Model.Update(sfreq, sduty);
        }
    }

    if (obj == instance->View.ui.duty.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            sduty = lv_spinbox_get_value(obj);
            instance->Model.Update(sfreq, sduty);
        }
    }

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
