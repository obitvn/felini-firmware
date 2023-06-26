#ifndef __Launcher_PRESENTER_H
#define __Launcher_PRESENTER_H

#include "LauncherView.h"
#include "LauncherModel.h"

namespace Page
{

class Launcher : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    Launcher();
    virtual ~Launcher();

    virtual void onCustomAttrConfig();
    virtual void onViewCreate();
    virtual void onViewLoop();
    virtual void onViewDestroy();


private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    LauncherView View;
    LauncherModel Model;
    lv_timer_t* timer;
};

}

#endif
