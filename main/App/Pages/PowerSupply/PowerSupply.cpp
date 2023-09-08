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

    volt.btn_state          =   0;
    volt.minval             =   3300;
    volt.maxval             =   21000;
    volt.step               =   1;

    current.btn_state       =   0;
    current.value           =   0;
    current.minval          =   0;
    current.maxval          =   3000;
    current.step            =   1;

    confirm.btn_state       =   0;
    config.status = PowerSupply::PD_SET_RELEASED;
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

    // AttachEvent((View.ui.slider.button));
    // AttachEvent(View.ui.spin.button);
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
    uint32_t key = lv_event_get_key(event);
    PowerSupply *instance = (PowerSupply *)lv_event_get_user_data(event);



    if (obj == instance->root)
    {
        // printf("root code event %d\r\n", code);
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_RIGHT == dir)
            {
                instance->Manager->Pop();
            }
        }
    }

    if(obj == instance->View.ui.spin.button)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            float level = (float)lv_spinbox_get_value(instance->View.ui.spin.button);
            printf("value change %f\r\n", level);
            switch (instance->config.status)
            {
                case PowerSupply::PD_SET_CURRENT:
                {
                    lv_label_set_text_fmt(instance->View.ui.current.set, "%.3f", (float)(level / 1000));
                    instance->current.value =  (float)(level / 1000);
                    break;
                }
                case PowerSupply::PD_SET_VOLT:
                {
                    lv_label_set_text_fmt(instance->View.ui.voltage.set, "%.3f", (float)(level / 1000));
                    instance->volt.value = (float)(level / 1000);
                    break;
                }
                case PowerSupply::PD_SET_POWER_ON:
                {
                    printf("power on \r\n");
                    break;
                }
                default:
                    lv_spinbox_set_value(instance->View.ui.spin.button, 0);
                    break;
            }
        }
    }

    if(obj == instance->View.ui.power.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->Model.PDSetUp(instance->volt.value, instance->current.value, instance->power.btn_state, PowerSupplyModel::PD_PDM_ON_OFF);
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
            instance->current.btn_state = !instance->current.btn_state;
            instance->View.FocusEditLabel(instance->View.ui.voltage.set, instance->View.ui.voltage.label, 0, &instance->volt.div);
            instance->View.FocusEditLabel(instance->View.ui.current.set, instance->View.ui.current.label, instance->current.btn_state, &instance->current.div);
            if (instance->current.btn_state > 0)
            {
                instance->config.status = PowerSupply::PD_SET_CURRENT;
            }
            else
            {
                float level = (float)lv_spinbox_get_value(instance->View.ui.spin.button);
                lv_label_set_text_fmt(instance->View.ui.current.label, "%.3f", (float)(instance->current.value));
                instance->config.status = PowerSupply::PD_SET_RELEASED;
            }
        }
    }
    if (obj == instance->View.ui.voltage.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->volt.btn_state = !instance->volt.btn_state;
            instance->View.FocusEditLabel(instance->View.ui.current.set, instance->View.ui.current.label, 0, &instance->current.div);
            instance->View.FocusEditLabel(instance->View.ui.voltage.set, instance->View.ui.voltage.label, instance->volt.btn_state, &instance->volt.div);
            if (instance->volt.btn_state > 0)
            {
                instance->config.status = PowerSupply::PD_SET_VOLT;
            }
            else
            {
                float level = (float)lv_spinbox_get_value(instance->View.ui.spin.button);
                lv_label_set_text_fmt(instance->View.ui.voltage.label, "%.3f", (float)(instance->volt.value));
                instance->config.status = PowerSupply::PD_SET_RELEASED;
            }
        }
    }
    if (obj == instance->View.ui.confirm.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->confirm.btn_state = !instance->confirm.btn_state;
            instance->View.FocusEditLabel(instance->View.ui.current.set, instance->View.ui.current.label, 0, &instance->current.div);
            instance->View.FocusEditLabel(instance->View.ui.voltage.set, instance->View.ui.voltage.label, 0, &instance->volt.div);
            instance->Model.PDSetUp(instance->volt.value, instance->current.value, 1, PowerSupplyModel::PD_PDM_ON_OFF);
        }
    }
}
