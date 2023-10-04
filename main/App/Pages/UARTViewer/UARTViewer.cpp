#include "UARTViewer.h"
#include <cstdio>


using namespace Page;

UARTViewer::UARTViewer()
{
}

UARTViewer::~UARTViewer()
{
}

void UARTViewer::onCustomAttrConfig()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_TOP, 500, lv_anim_path_ease_in);



    
}

void UARTViewer::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    AttachEvent(root);
    lv_obj_set_user_data(View.ui.keyboard.cont, this);
    lv_obj_set_user_data(View.ui.text.cont, this);

    lv_obj_add_event_cb(View.ui.keyboard.cont, onEvent, LV_EVENT_ALL, this);
    lv_obj_add_event_cb(View.ui.text.cont, onEvent, LV_EVENT_ALL, this);

    timer = lv_timer_create(onTimer, 50, this);
    lv_timer_set_repeat_count(timer, -1); // infinity
}

void UARTViewer::onViewDidLoad()
{
}

void UARTViewer::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void UARTViewer::onViewDidAppear()
{
    
}

void UARTViewer::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void UARTViewer::onViewDidDisappear()
{
}

void UARTViewer::onViewDidUnload()
{
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_OVER_BOTTOM, 500, lv_anim_path_ease_in);
    View.Delete();
    Model.Deinit();
}

void UARTViewer::AttachEvent(lv_obj_t *obj)
{
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_GESTURE, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void UARTViewer::Update(lv_timer_t *timer)
{
    UARTViewer *instance = (UARTViewer *)timer->user_data;
    static HAL::UART_Info_t uart;
    uart.cmd = HAL::CMD_RECV;
    Model.Update(&uart);
    if(uart.receive != NULL)
    {
        printf("text: %s\n", uart.receive);
        lv_textarea_add_text(instance->View.ui.text.cont, uart.receive);
    }
}

void UARTViewer::onTimer(lv_timer_t *timer)
{
    UARTViewer *instance = (UARTViewer *)timer->user_data;
    instance->Update(timer);
}




void UARTViewer::onEvent(lv_event_t *event)
{

    lv_obj_t *obj = lv_event_get_target(event);
    lv_event_code_t code = lv_event_get_code(event);
    UARTViewer *instance = (UARTViewer *)lv_obj_get_user_data(obj);

    if(obj == instance->View.ui.text.cont)
    {
        if(LV_EVENT_CLICKED == code)
        {
            if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD)
            {
                lv_obj_clear_flag(instance->View.ui.keyboard.cont, LV_OBJ_FLAG_HIDDEN);
            }
        }

        if (LV_EVENT_DEFOCUSED == code)
        {
            lv_obj_add_flag(instance->View.ui.keyboard.cont, LV_OBJ_FLAG_HIDDEN);
        }
    }

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
