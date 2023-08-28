#include "PowerSupply.h"
#include <cstdio>


using namespace Page;

PowerSupply::PowerSupply()
{
}

PowerSupply::~PowerSupply()
{
}

void PowerSupply::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);
    power.btn_state = 0;
    volt.btn_state   =0;
    current.btn_state     =0;
    current.value = 0;
    confirm.btn_state   =0;
}

void PowerSupply::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    
    lv_obj_set_user_data(root, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_SCROLL, this);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    PowerSupplyView::item_t *item_grp = ((PowerSupplyView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(PowerSupplyView::item_t); i++)
    {
        AttachEvent(item_grp[i].button);
    }

    AttachEvent((View.ui.slider.button));
}

void PowerSupply::onViewDidLoad()
{
}

void PowerSupply::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void PowerSupply::onViewDidAppear()
{
    
}

void PowerSupply::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void PowerSupply::onViewDidDisappear()
{
}

void PowerSupply::onViewDidUnload()
{
    Model.Deinit();
    View.Delete();
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
}

void PowerSupply::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void PowerSupply::Update()
{

}

void PowerSupply::onTimer(lv_timer_t *timer)
{

}


static uint8_t power_state = 0;

void PowerSupply::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    PowerSupply *instance = (PowerSupply *)lv_obj_get_user_data(obj);


    if (obj == instance->root)
    {
        printf("root code event %d\r\n", code);
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_RIGHT == dir)
            {
                instance->Manager->Pop();
            }
        }
    }

    if(obj ==instance->View.ui.slider.button)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            printf("scroll \r\n");
            switch (instance->config.status)
            {
                
                case PowerSupply::PD_SET_CURRENT:
                {
                    int32_t level = lv_slider_get_value(obj);
                    lv_label_set_text_fmt(instance->View.ui.current.label, "%.2f", level);
                    break;
                }
                case PowerSupply::PD_SET_VOLT:
                {
                    int32_t level = lv_slider_get_value(obj);
                    lv_label_set_text_fmt(instance->View.ui.voltage.label, "%.2f", level);
                    break;
                }
                case PowerSupply::PD_SET_POWER_ON:
                {
                    printf("power on \r\n");
                    break;
                }

                default:
                    break;
            }
        }
        if (code == LV_EVENT_PRESSED)
        {
            printf("presss\r\n");
        }
    }

    if(obj == instance->View.ui.power.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->Model.PDSetUp(0, 0, instance->power.btn_state, PowerSupplyModel::PD_PDM_ON_OFF);
            instance->power.btn_state = !instance->power.btn_state;
            if (instance->volt.btn_state)
            {
                instance->config.status = PowerSupply::PD_SET_POWER_ON;
            }
            else
                instance->config.status = PowerSupply::PD_SET_RELEASED;
        }
    }
    if (obj == instance->View.ui.current.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->View.FocusEditLabel(instance->View.ui.current.label, instance->current.btn_state);
            instance->current.btn_state = !instance->current.btn_state;
            if (instance->current.btn_state)
            {
                instance->config.status = PowerSupply::PD_SET_CURRENT;
                // lv_slider_set_value(instance->View.ui.slider.button, 15, LV_ANIM_OFF);
                // lv_slider_set_range(instance->View.ui.slider.button, 10, 10*300);
            }
            else
                instance->config.status = PowerSupply::PD_SET_RELEASED;
        }
    }
    if (obj == instance->View.ui.voltage.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->View.FocusEditLabel(instance->View.ui.voltage.label, instance->volt.btn_state);
            instance->volt.btn_state = !instance->volt.btn_state;
            if (instance->volt.btn_state)
            {
                instance->config.status = PowerSupply::PD_SET_VOLT;
                // lv_slider_set_value(instance->View.ui.slider.button, 15, LV_ANIM_OFF);
                // lv_slider_set_range(instance->View.ui.slider.button, 3300, 21000);
            }
            else
                instance->config.status = PowerSupply::PD_SET_RELEASED;
        }
    }
    if (obj == instance->View.ui.confirm.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->confirm.btn_state = !instance->confirm.btn_state;
        }
    }
}
