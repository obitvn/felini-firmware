#include "Hertz.h"
#include <cstdio>


using namespace Page;

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

    lv_obj_set_user_data(root, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    HertzView::item_t *item_grp = ((HertzView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(HertzView::item_t); i++)
    {
        AttachEvent(item_grp[i].btn);
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



    if(obj == instance->View.ui.frequency.btn)
    {
        if (code == LV_EVENT_CLICKED)
        {
            instance->View.ui.frequency.state = !instance->View.ui.frequency.state;
            if (instance->View.ui.frequency.state)
            {
                instance->View.ui.duty.state = false;
                lv_obj_set_style_bg_opa(instance->View.ui.duty.btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                instance->View.ui.panel.state = false;
                lv_obj_set_style_bg_opa(instance->View.ui.panel.btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                instance->View.ui.frequency.state = true;
                lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_FOCUSED);

                lv_spinbox_set_cursor_pos(instance->View.ui.spin.cont, 7);
                lv_spinbox_set_digit_format(instance->View.ui.spin.cont, 7, 0);
                lv_spinbox_set_range(instance->View.ui.spin.cont, 0, 8000000);
                lv_spinbox_set_step(instance->View.ui.spin.cont, 1);
                lv_spinbox_set_value(instance->View.ui.spin.cont, instance->View.ui.frequency.value);
            }
            else
            {
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }
    }

    if (obj == instance->View.ui.duty.btn)
    {
        if (code == LV_EVENT_CLICKED)
        {
            instance->View.ui.duty.state = !instance->View.ui.duty.state;
            if (instance->View.ui.duty.state)
            {
                instance->View.ui.panel.state = false;
                lv_obj_set_style_bg_opa(instance->View.ui.panel.btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                instance->View.ui.frequency.state = false;
                lv_obj_set_style_bg_opa(instance->View.ui.frequency.btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                instance->View.ui.duty.state = true;
                lv_obj_set_style_bg_opa(instance->View.ui.duty.btn, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_FOCUSED);

                lv_spinbox_set_cursor_pos(instance->View.ui.spin.cont, 2);
                lv_spinbox_set_digit_format(instance->View.ui.spin.cont, 2, 0);
                lv_spinbox_set_range(instance->View.ui.spin.cont, 0, 100);
                lv_spinbox_set_step(instance->View.ui.spin.cont, 1);
                lv_spinbox_set_value(instance->View.ui.spin.cont, instance->View.ui.duty.value);
            }
            else 
            {
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
            
        }
    }

    if (obj == instance->View.ui.panel.btn)
    {
        if (code == LV_EVENT_CLICKED)
        {
            instance->View.ui.panel.state = !instance->View.ui.panel.state;
            if (instance->View.ui.panel.state)
            {
                instance->View.ui.panel.state = true;
                lv_obj_set_style_bg_opa(instance->View.ui.panel.btn, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_bg_opa(obj, 100, LV_PART_MAIN | LV_STATE_FOCUSED);

                instance->View.ui.frequency.state = false;
                lv_obj_set_style_bg_opa(instance->View.ui.frequency.btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

                instance->View.ui.duty.state = false;
                lv_obj_set_style_bg_opa(instance->View.ui.duty.btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            else
            {
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
                lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_PRESSED);
                // lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
            }
        }
    }

    if(obj == instance->View.ui.spin.btn)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            float val = (float)lv_spinbox_get_value(instance->View.ui.spin.btn);
            printf("value change %f\r\n", val);
            if (instance->View.ui.frequency.state)
            {
                if (val > 1000000)
                {
                    val = val / 1000000;
                    lv_label_set_text_fmt(instance->View.ui.frequency.cont, "%.0f", (float)(val/ 1000000));
                    lv_label_set_text(instance->View.ui.unit.cont, "Mhz");
                }
                else if (val > 1000)
                {
                    val = val / 1000;
                    lv_label_set_text_fmt(instance->View.ui.frequency.cont, "%.0f", (float)( val / 1000));
                    lv_label_set_text(instance->View.ui.unit.cont, "Khz");
                }
                else
                {
                    lv_label_set_text_fmt(instance->View.ui.frequency.cont, "%.0f", (float)(val));
                    lv_label_set_text(instance->View.ui.unit.cont, "Hz");
                }
            }
            else if (instance->View.ui.duty.state)
            {
                lv_label_set_text_fmt(instance->View.ui.duty.cont, "%.0f%%", val);
            }
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
