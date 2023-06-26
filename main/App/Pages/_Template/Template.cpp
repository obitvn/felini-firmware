#include "Template.h"
#include <cstdio>

using namespace Page;

Template::Template()
{
}

Template::~Template()
{

}

void Template::onCustomAttrConfig()
{
    SetCustomCacheEnable(true);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_RIGHT, 600, lv_anim_path_bounce);
}

void Template::onViewLoad()
{
    View.Create(root);

    Model.TickSave = Model.GetData();
}

void Template::onViewDidLoad()
{
    AttachEvent(root);
}

void Template::onViewWillAppear()
{
    Param_t param;
    // param.color = lv_color_black();
    param.color = LV_COLOR_MAKE16(54, 123, 175);
    param.time = 600;

    PAGE_STASH_POP(param);

    lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
    timer = lv_timer_create(onTimerUpdate, param.time, this);
}

void Template::onViewDidAppear()
{
    lv_timer_resume(timer);
}

void Template::onViewWillDisappear()
{

}

void Template::onViewDidDisappear()
{
    lv_timer_pause(timer);

}

void Template::onViewDidUnload()
{
    lv_obj_remove_event_cb(root, onEvent);
}

void Template::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void Template::Update()
{
    // lv_label_set_text_fmt(View.ui.labelTick, "tick = %d save = %d", Model.GetData(), Model.TickSave);
}

void Template::onTimerUpdate(lv_timer_t *timer)
{
    Template *instance = (Template *)timer->user_data;

    instance->Update();
}

void Template::onEvent(lv_event_t *event)
{
    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    Template *instance = (Template *)lv_obj_get_user_data(obj);

    if (obj == instance->root) {
        if (LV_EVENT_GESTURE == code) {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_LEFT == dir) {
                instance->Manager->Pop();
            }
        }
    }
}
