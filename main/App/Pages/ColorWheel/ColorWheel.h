#ifndef __ColorWheel_PRESENTER_H
#define __ColorWheel_PRESENTER_H

#include "ColorWheelView.h"
#include "ColorWheelModel.h"

namespace Page
{

class ColorWheel : public PageBase
{
public:

public:
    ColorWheel();
    virtual ~ColorWheel();

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
    ColorWheelView View;
    ColorWheelModel Model;
};

}

#endif
