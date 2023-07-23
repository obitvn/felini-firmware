#include "StartUp.h"

using namespace Page;

Startup::Startup()
{
}

Startup::~Startup()
{
}

void Startup::onCustomAttrConfig()
{
    SetCustomCacheEnable(false);
    SetCustomLoadAnimType(PageManager::LOAD_ANIM_NONE);
}

void Startup::onViewLoad()
{
    Model.Init();
    View.Create(root);
    lv_timer_t *timer = lv_timer_create(onTimer, 3000, this);
    lv_timer_set_repeat_count(timer, 1);
}

void Startup::onViewDidLoad()
{
    lv_obj_fade_out(root, 500, 2500);
}

void Startup::onViewWillAppear()
{
    lv_anim_timeline_start(View.ui.anim_timeline);
}

void Startup::onViewDidAppear()
{
}

void Startup::onViewWillDisappear()
{
}

void Startup::onViewDidDisappear()
{
}

void Startup::onViewDidUnload()
{
    View.Delete();
    Model.Deinit();
}

void Startup::onTimer(lv_timer_t *timer)
{
    Startup *instance = (Startup *)timer->user_data;

    instance->Manager->Push("Pages/HappyBirthday");
    // instance->Manager->Push("Pages/Dialplate");
}

void Startup::onEvent(lv_event_t *event)
{
}
