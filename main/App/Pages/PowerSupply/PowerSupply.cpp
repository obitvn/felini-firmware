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
    btn_volt_state      =0;
    btn_current_state   =0;
    btn_power_state     =0;
    btn_confirm_state   =0;
}

void PowerSupply::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    
    lv_obj_set_user_data(root, this);
    lv_obj_add_event_cb(root, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(root, LV_OBJ_FLAG_SCROLLABLE);

    PowerSupplyView::item_t *item_grp = ((PowerSupplyView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(PowerSupplyView::item_t); i++)
    {
        AttachEvent(item_grp[i].button);
    }
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
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_RIGHT == dir)
            {
                instance->Manager->Pop();
            }
        }
    }


    if(obj == instance->View.ui.power.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->Model.PDSetUp(0, 0, instance->btn_power_state, PowerSupplyModel::PD_PDM_ON_OFF);
            instance->btn_power_state = !instance->btn_power_state;
        }
    }
    if (obj == instance->View.ui.current.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            
        }
    }
    if (obj == instance->View.ui.voltage.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            
        }
    }
    if (obj == instance->View.ui.confirm.button)
    {
        if (code == LV_EVENT_PRESSED)
        {
            
        }
    }
}
