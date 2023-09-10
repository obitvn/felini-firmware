#ifndef __SYSTEM_INFOS_PRESENTER_H
#define __SYSTEM_INFOS_PRESENTER_H

#include "AppInfosView.h"
#include "AppInfosModel.h"

namespace Page
{

class AppInfos : public PageBase
{
public:

public:
    AppInfos();
    virtual ~AppInfos();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();

private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    void onFoucusUp();
    void onFoucusDown();
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);
    static int16_t pos;

private:
    AppInfosView View;
    AppInfosModel Model;
    lv_timer_t* timer;
};

}

#endif
