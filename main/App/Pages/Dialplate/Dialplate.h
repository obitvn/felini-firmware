#ifndef __Dialplate_PRESENTER_H
#define __Dialplate_PRESENTER_H

#include "DialplateView.h"
#include "DialplateModel.h"

namespace Page
{

class Dialplate : public PageBase
{
public:

public:
    Dialplate();
    virtual ~Dialplate();

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
    DialplateView View;
    DialplateModel Model;
};

}

#endif
