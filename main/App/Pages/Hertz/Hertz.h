#ifndef __Hertz_PRESENTER_H
#define __Hertz_PRESENTER_H

#include "HertzView.h"
#include "HertzModel.h"

namespace Page
{

class Hertz : public PageBase
{
public:

public:
    Hertz();
    virtual ~Hertz();

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
    HertzView View;
    HertzModel Model;

};

}

#endif
