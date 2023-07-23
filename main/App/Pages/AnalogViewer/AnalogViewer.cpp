#include "AnalogViewer.h"
#include <cstdio>


using namespace Page;

AnalogViewer::AnalogViewer()
{
}

AnalogViewer::~AnalogViewer()
{
}

void AnalogViewer::onCustomAttrConfig()
{
    
}

void AnalogViewer::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    // AttachEvent(View.scroll_panel.cont);


}

void AnalogViewer::onViewDidLoad()
{
}

void AnalogViewer::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void AnalogViewer::onViewDidAppear()
{
    
}

void AnalogViewer::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void AnalogViewer::onViewDidDisappear()
{
}

void AnalogViewer::onViewDidUnload()
{
    View.Delete();
    Model.Deinit();
}

void AnalogViewer::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AnalogViewer::Update()
{

}

void AnalogViewer::onTimer(lv_timer_t *timer)
{

}




void AnalogViewer::onEvent(lv_event_t *event)
{

    AnalogViewer *instance = (AnalogViewer *)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);
    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_PRESSED)
    {
        // printf("LV_EVENT_PRESSED\r\n");
        instance->Manager->Pop();
    }
}
