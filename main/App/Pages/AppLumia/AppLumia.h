#ifndef __AppLumia_PRESENTER_H
#define __AppLumia_PRESENTER_H

#include "AppLumiaView.h"
#include "AppLumiaModel.h"

namespace Page
{

class AppLumia : public PageBase
{
public:

public:
    AppLumia();
    virtual ~AppLumia();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    void Update();
    void AttachEvent(lv_obj_t *obj);
    void ViewUpdatePos(lv_event_t *event);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    AppLumiaView View;
    AppLumiaModel Model;
};

}

#endif
