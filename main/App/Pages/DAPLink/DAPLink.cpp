#include "DAPLink.h"
#include <cstdio>


using namespace Page;

DAPLink::DAPLink()
{
}

DAPLink::~DAPLink()
{
}

void DAPLink::onCustomAttrConfig()
{
    
}

void DAPLink::onViewLoad()
{
    Model.DAPCommand(12); // crash
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(View.switch_cont);
    
}

void DAPLink::onViewDidLoad()
{
}

void DAPLink::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void DAPLink::onViewDidAppear()
{
    
}

void DAPLink::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void DAPLink::onViewDidDisappear()
{
}

void DAPLink::onViewDidUnload()
{
    Model.DAPCommand(6);
    View.Delete();
    Model.Deinit();
}

void DAPLink::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void DAPLink::Update()
{

}

void DAPLink::onTimer(lv_timer_t *timer)
{

}

static int value = 0;

void DAPLink::enableHW(int value)
{
    Model.DAPCommand(value );
}



void DAPLink::onEvent(lv_event_t *event)
{

    DAPLink *instance = (DAPLink *)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);
    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    // if (code == LV_EVENT_PRESSED)
    // {
    //     // printf("LV_EVENT_PRESSED\r\n");
    //     instance->Manager->Pop();
    // }

    if (code == LV_EVENT_VALUE_CHANGED)
    {
        // value++;
        printf("State changed\n");
        // instance->enableHW(value);
        instance->Manager->Pop(); //crash
    }

}
