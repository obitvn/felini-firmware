#include "HappyBirthday.h"
#include <cstdio>


using namespace Page;

HappyBirthday::HappyBirthday()
{
}

HappyBirthday::~HappyBirthday()
{
}

void HappyBirthday::onCustomAttrConfig()
{
    
}

void HappyBirthday::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    // AttachEvent(View.scroll_panel.cont);


}

void HappyBirthday::onViewDidLoad()
{
}

void HappyBirthday::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void HappyBirthday::onViewDidAppear()
{
    
}

void HappyBirthday::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void HappyBirthday::onViewDidDisappear()
{
}

void HappyBirthday::onViewDidUnload()
{
    View.Delete();
    Model.Deinit();
}

void HappyBirthday::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void HappyBirthday::Update()
{

}

void HappyBirthday::onTimer(lv_timer_t *timer)
{

}




void HappyBirthday::onEvent(lv_event_t *event)
{

    // HappyBirthday *instance = (HappyBirthday *)lv_event_get_user_data(event);
    // LV_ASSERT_NULL(instance);


    // lv_obj_t *obj = lv_event_get_current_target(event);
    // lv_event_code_t code = lv_event_get_code(event);



}
