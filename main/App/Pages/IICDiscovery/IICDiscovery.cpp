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
    
}

void IICDiscovery::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    // AttachEvent(View.scroll_panel.cont);


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
    View.Delete();
    Model.Deinit();
}

void IICDiscovery::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void IICDiscovery::Update()
{

}

void IICDiscovery::onTimer(lv_timer_t *timer)
{

}




void IICDiscovery::onEvent(lv_event_t *event)
{

    IICDiscovery *instance = (IICDiscovery *)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);


    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);



}
