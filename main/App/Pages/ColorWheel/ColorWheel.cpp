#include "ColorWheel.h"
#include <cstdio>


using namespace Page;

ColorWheel::ColorWheel()
{
}

ColorWheel::~ColorWheel()
{
}

void ColorWheel::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void ColorWheel::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(root);
    lv_obj_set_user_data(View.ui.color.cont, this);
    lv_obj_add_event_cb(View.ui.color.cont, onEvent, LV_EVENT_ALL, this);
}

void ColorWheel::onViewDidLoad()
{
}

void ColorWheel::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void ColorWheel::onViewDidAppear()
{
    
}

void ColorWheel::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void ColorWheel::onViewDidDisappear()
{
}

void ColorWheel::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void ColorWheel::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void ColorWheel::Update(lv_color_t *color)
{
    uint16_t value = (uint16_t)color->full;
    uint8_t r = (value >> 11) & 0b11111; // Lấy 5 bit đầu tiên
    uint8_t g = (value >> 5) & 0b111111; // Lấy 6 bit tiếp theo
    uint8_t b = value & 0b11111;         // Lấy 5 bit cuối cùng
    Model.Update(r, g, b);
}

void ColorWheel::onTimer(lv_timer_t *timer)
{

}

void ColorWheel::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    ColorWheel *instance = (ColorWheel *)lv_obj_get_user_data(obj);

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

    if (obj == instance->View.ui.color.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            lv_color_t color_val = lv_colorwheel_get_rgb(instance->View.ui.color.cont);
            instance->Update(&color_val);
        }
    }
}
