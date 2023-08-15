#include "Dialplate.h"
#include <cstdio>


using namespace Page;

Dialplate::Dialplate()
{
}

Dialplate::~Dialplate()
{
}

void Dialplate::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 600, lv_anim_path_ease_in);



    
}

void Dialplate::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(View.scroll_panel.cont);

    DialplateView::item_t *item_grp = ((DialplateView::item_t *)&View.ui);
    for (int i = 0; i < sizeof(View.ui) / sizeof(DialplateView::item_t); i++)
    {
        AttachEvent(item_grp[i].cont);
    }
}

void Dialplate::onViewDidLoad()
{
}

void Dialplate::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void Dialplate::onViewDidAppear()
{
    
}

void Dialplate::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void Dialplate::onViewDidDisappear()
{
}

void Dialplate::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 600, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void Dialplate::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void Dialplate::Update()
{

}

void Dialplate::onTimer(lv_timer_t *timer)
{

}

void Dialplate::ViewUpdatePos(lv_event_t *event)
{
    lv_obj_t *cont = lv_event_get_target(event);
    View.UpdatePosItem(cont);
}


void Dialplate::onEvent(lv_event_t *event)
{

    Dialplate *instance = (Dialplate *)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    DialplateView::item_t *item_grp = ((DialplateView::item_t *)&instance->View.ui);

    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->View.scroll_panel.cont)
    {
        if (code == LV_EVENT_SCROLL)
            instance->ViewUpdatePos(event);
    }

    for (int i = 0; i < sizeof(instance->View.ui) / sizeof(DialplateView::item_t); i++)
    {
        // AttachEvent(item_grp[i].cont);
        if (obj == item_grp[i].cont) //
        {
            if (code == LV_EVENT_CLICKED)
            {
                // printf("pressing at button %d app_src %s\r\n", i, item_grp[i].labelInfo);
                // instance->Manager->Pop(); //đóng page và quay về page trước đó
                // instance->Manager->Push("Pages/IICDiscovery"); // load page mới, đang lỗi chưa load được
            }
        }
    }


}
