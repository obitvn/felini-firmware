#include "IICDiscovery.h"
#include <cstdio>


using namespace Page;

IICDiscovery::IICDiscovery()
{
}

IICDiscovery::~IICDiscovery()
{
}

void IICDiscovery::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void IICDiscovery::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(root);

    timer = lv_timer_create(onTimer, 50, this);
    lv_timer_set_repeat_count(timer, -1); // infinity

    IICDiscoveryView::item_t *item_grp = ((IICDiscoveryView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(IICDiscoveryView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
}

void IICDiscovery::onViewDidLoad()
{
}

void IICDiscovery::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void IICDiscovery::onViewDidAppear()
{
    
}

void IICDiscovery::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void IICDiscovery::onViewDidDisappear()
{
}

void IICDiscovery::onViewDidUnload()
{
    lv_timer_del(timer);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void IICDiscovery::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void IICDiscovery::Update()
{

}

uint8_t add=0;

void IICDiscovery::Update(lv_timer_t *timer)
{
    static HAL::IIC_Info_t iic_info;
    iic_info.addr = add;
    iic_info.cmd  = HAL::CMD_UPDATE;
    Model.Scan(&iic_info);
    IICDiscovery *instance = (IICDiscovery *)timer->user_data;
    lv_bar_set_value(instance->View.ui.bar.cont, add, LV_ANIM_OFF);
    lv_label_set_text_fmt(instance->View.ui.addr.cont, "0x%02x", add++);
    char data[10];
    sprintf(data, "0x%02x ", iic_info.addr);
    if (iic_info.status)
    {
        lv_textarea_add_text(instance->View.ui.terminal.cont, data);
    }
}

void IICDiscovery::onTimer(lv_timer_t *timer)
{
    IICDiscovery *instance = (IICDiscovery *)timer->user_data;
    instance->Update(timer);
}




void IICDiscovery::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    IICDiscovery *instance = (IICDiscovery *)lv_obj_get_user_data(obj);

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
