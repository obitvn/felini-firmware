#include "Interval.h"
#include <cstdio>


using namespace Page;

Interval::Interval()
{
}

Interval::~Interval()
{
}

void Interval::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);
}

void Interval::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);
    timer = lv_timer_create(onTimer, 1000, this);
    lv_timer_set_repeat_count(timer, -1); // infinity
    AttachEvent(root);
}

void Interval::onViewDidLoad()
{
}

void Interval::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void Interval::onViewDidAppear()
{
    
}

void Interval::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void Interval::onViewDidDisappear()
{
}

void Interval::onViewDidUnload()
{
    lv_timer_del(timer);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void Interval::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void Interval::Update(lv_timer_t *timer)
{
    float val = 0;
    Interval *instance = (Interval *)timer->user_data;
    static HAL::IntervalTime_Info_t f;
    f.frequency = 0;
    Model.Update(&f);
    if (f.frequency != NULL)
        val = f.frequency;

    if(val > 1000000) 
    {
        val = val / 1000000;
        lv_label_set_text_fmt(instance->View.ui.time.cont, "%.2f nS", (float)((1/val) * 1000));
        lv_label_set_text(instance->View.ui.unit.cont, "Mhz");
    }
    else if(val > 1000) 
    {
        val = val / 1000;
        lv_label_set_text_fmt(instance->View.ui.time.cont, "%.2f uS", (float)((1/val) * 1000));
        lv_label_set_text(instance->View.ui.unit.cont, "Khz");
    }
    else 
    {
        lv_label_set_text_fmt(instance->View.ui.time.cont, "%.2f mS", (float)((1/val) * 1000));
        lv_label_set_text(instance->View.ui.unit.cont, "Hz");
    }
    lv_label_set_text_fmt(instance->View.ui.freq.cont, "%.2f", (float)(val));
}

void Interval::onTimer(lv_timer_t *timer)
{
    Interval *instance = (Interval *)timer->user_data;
    instance->Update(timer);
}




void Interval::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    Interval *instance = (Interval *)lv_obj_get_user_data(obj);

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
