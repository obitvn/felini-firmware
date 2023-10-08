#include "PowerSupply.h"
#include <cstdio>


using namespace Page;

bool setup = false;

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

    timer = lv_timer_create(onTimer, 100, this);
    lv_timer_set_repeat_count(timer, -1); //infinity

    PowerSupplyView::item_t *item_grp = ((PowerSupplyView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(PowerSupplyView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
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
    lv_timer_del(timer);
    View.Delete();
    Model.Deinit();
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
}

void PowerSupply::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
}

void PowerSupply::Update(lv_timer_t *timer)
{
    HAL::PowerPD_Info_t pd;
    PowerSupply *instance = (PowerSupply *)timer->user_data;
    Model.GetPDInfo(&pd);
    printf("upd pdate vol %d\n", pd.get_voltage);
    if(!setup)
    {
        lv_spinbox_set_value(instance->View.ui.voltage.cont, pd.get_voltage);
        lv_spinbox_set_value(instance->View.ui.current.cont, pd.get_current);
    }
}

void PowerSupply::onTimer(lv_timer_t *timer)
{
    PowerSupply *instance = (PowerSupply *)timer->user_data;
    instance->Update(timer);
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
        if (LV_EVENT_GESTURE == code)
        {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (LV_DIR_RIGHT == dir)
            {
                instance->Manager->Pop();
            }
            else if (LV_DIR_LEFT == dir)
            {
                instance->Manager->Push("Pages/PowerList");
            }
        }
    }

    if (obj == instance->View.ui.voltage.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            instance->volt.value = lv_spinbox_get_value(obj);
        }
    }

    if (obj == instance->View.ui.current.cont)
    {
        if (code == LV_EVENT_VALUE_CHANGED)
        {
            instance->current.value = lv_spinbox_get_value(obj);
        }
    }

    if(obj == instance->View.ui.power_btn.cont)
    {
        if (code == LV_EVENT_PRESSED)
        {
            instance->Model.PDSetUp(instance->volt.value, instance->current.value, instance->power.btn_state, PowerSupplyModel::PD_PDM_ON_OFF);
            if (instance->power.btn_state)
            {
                setup = false;
                instance->Model.PDSetUp(instance->volt.value, instance->current.value, false, PowerSupplyModel::PD_PDM_ON_CONFIG);
                instance->Model.PDSetUp(instance->volt.value, instance->current.value, true, PowerSupplyModel::PD_PDM_ON_OFF);
                // printf("volt %d, cur %ld\n", instance->volt.value, instance->current.value);
                lv_obj_clear_state(instance->View.ui.voltage.cont, LV_STATE_FOCUSED);
                lv_obj_clear_state(instance->View.ui.current.cont, LV_STATE_FOCUSED);
                lv_label_set_text_fmt(instance->View.ui.set_volt.cont, "%.3f", (float)((float)instance->volt.value / 1000));
                lv_label_set_text_fmt(instance->View.ui.set_amp.cont, "%.1f", (float)(instance->current.value / 10));
                lv_label_set_text_fmt(instance->View.ui.status.cont, "ATIVATE");
                lv_obj_set_style_text_color(instance->View.ui.status.cont, lv_color_hex(0x15CC34), LV_PART_MAIN | LV_STATE_DEFAULT);
            }
            else
            {
                setup = true;
                instance->config.status = PowerSupply::PD_SET_RELEASED;
                lv_label_set_text_fmt(instance->View.ui.status.cont, "DEATIVATE");
                lv_obj_set_style_text_color(instance->View.ui.status.cont, lv_color_hex(0xe5534b), LV_PART_MAIN | LV_STATE_DEFAULT);
                instance->Model.PDSetUp(0, 0, false, PowerSupplyModel::PD_PDM_ON_OFF);
            }
            instance->power.btn_state = !instance->power.btn_state;
        }
    }



}
