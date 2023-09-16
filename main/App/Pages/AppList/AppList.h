#ifndef __SYSTEM_INFOS_PRESENTER_H
#define __SYSTEM_INFOS_PRESENTER_H

#include "AppListView.h"
#include "AppListModel.h"

namespace Page
{

class AppList : public PageBase
{
public:

public:
    AppList();
    virtual ~AppList();

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
    AppListView View;
    AppListModel Model;
    lv_timer_t* timer;
};

}

#endif
