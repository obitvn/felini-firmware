#include "ServoCtrl.h"
#include <cstdio>


using namespace Page;

ServoCtrl::ServoCtrl()
{
}

ServoCtrl::~ServoCtrl()
{
}

void ServoCtrl::onCustomAttrConfig()
{
    
}

void ServoCtrl::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    // AttachEvent(View.scroll_panel.cont);


}

void ServoCtrl::onViewDidLoad()
{
}

void ServoCtrl::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void ServoCtrl::onViewDidAppear()
{
    
}

void ServoCtrl::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void ServoCtrl::onViewDidDisappear()
{
}

void ServoCtrl::onViewDidUnload()
{
    View.Delete();
    Model.Deinit();
}

void ServoCtrl::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void ServoCtrl::Update()
{

}

void ServoCtrl::onTimer(lv_timer_t *timer)
{

}




void ServoCtrl::onEvent(lv_event_t *event)
{

    // ServoCtrl *instance = (ServoCtrl *)lv_event_get_user_data(event);
    // LV_ASSERT_NULL(instance);


    // lv_obj_t *obj = lv_event_get_current_target(event);
    // lv_event_code_t code = lv_event_get_code(event);



}
