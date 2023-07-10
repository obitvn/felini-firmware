#include <cstdio>
#include "MenuList.h"

using namespace Page;

MenuList::MenuList()
{
}

MenuList::~MenuList()
{
}

void MenuList::onCustomAttrConfig()
{
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void MenuList::onViewLoad()
{
    
    Model.Init(); // DataCenter
    View.Create(root);

    AttachEvent(root);
    AttachEvent(View.ui.back);
    // AttachEvent(View.ui.list_menu);
    AttachEvent(View.ui.home);
    // AttachEvent(View.ui.settings);
    // AttachEvent(View.ui.remove);
    AttachEvent(View.ui.control);
    
    StatusBar::Appear(true);
}

void MenuList::onViewDidLoad()
{
}

void MenuList::onViewWillAppear()
{
    Param_t param;
    param.color = LV_COLOR_MAKE16(0, 0, 0);
    param.time = 500;

    PAGE_STASH_POP(param);

    lv_obj_set_style_bg_color(root, param.color, LV_PART_MAIN);
    timer = lv_timer_create(onTimerUpdate, param.time, this);
}

void MenuList::onViewDidAppear()
{
    lv_timer_resume(timer);
}

void MenuList::onViewWillDisappear()
{
}

void MenuList::onViewDidDisappear()
{
    lv_timer_pause(timer);
}

void MenuList::onViewDidUnload()
{
    Model.Deinit();
    View.Delete();
}

void MenuList::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void MenuList::Update()
{
    // lv_label_set_text(View.ui.read_voltage, "12.01");
}

void MenuList::onTimerUpdate(lv_timer_t *timer)
{
    MenuList *instance = (MenuList *)timer->user_data;

    instance->Update();
}

void MenuList::onShow()
{
    View.ShowControlPanel();
}

void MenuList::settoDefault()
{
    View.SetDefaultControlPanel();
}

void MenuList::onEvent(lv_event_t *event)
{

    MenuList *instance = (MenuList *)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t *obj = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);


    if (obj == instance->View.ui.control)
    {
        // if (code == LV_EVENT_PRESSING)
        // {
            lv_indev_t *indev = lv_indev_get_act();
            if (indev == NULL)
                return;

            lv_point_t vect;
            lv_coord_t x, y;
            lv_indev_get_vect(indev, &vect);
            lv_coord_t get_x = lv_obj_get_x(obj);
            lv_coord_t get_y = lv_obj_get_y(obj);
            y = get_y; 
            x = get_x + vect.x;
            printf("x %d y %d get_x %d get_y %d vect_x %d vecty %d\r\n", x, y, get_x, get_y, vect.x, vect.y);
            lv_obj_set_pos(obj, x, y);

            if(x < 200)
            {
                // lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
                // instance->onShow();
            }
        // }
    }
    // if (obj == instance->View.ui.back)
    // {
    //     if (code == LV_EVENT_PRESSING)
    //         instance->settoDefault();
    // }

    if (obj == instance->View.ui.home)
    {
        if (code == LV_EVENT_PRESSING)
        {
            printf("home\r\n");
            instance->Manager->BackHome(); // về home
        }
    }

    if (obj == instance->View.ui.setting)
    {
        if (code == LV_EVENT_PRESSING)
        {
            printf("dialplate\r\n");
            instance->Manager->Push("Pages/Dialplate"); //load page mới
        }
    }

    if (obj == instance->View.ui.back)
    {
        if (code == LV_EVENT_PRESSING)
        {
            printf("remove\r\n");
            instance->Manager->Pop(); //sẽ close page hiện tại và load lại page cũ trước đó
        }
    }
}
