#ifndef __Interval_PRESENTER_H
#define __Interval_PRESENTER_H

#include "IntervalView.h"
#include "IntervalModel.h"

namespace Page
{

class Interval : public PageBase
{
public:

public:
    Interval();
    virtual ~Interval();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    void Update(lv_timer_t *timer);
    void AttachEvent(lv_obj_t *obj);
    void ViewUpdatePos(lv_event_t *event);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    IntervalView View;
    IntervalModel Model;

private:
    lv_timer_t *timer;
};

}

#endif
