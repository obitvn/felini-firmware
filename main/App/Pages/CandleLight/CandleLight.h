#ifndef __CandleLight_PRESENTER_H
#define __CandleLight_PRESENTER_H

#include "CandleLightView.h"
#include "CandleLightModel.h"

namespace Page
{

class CandleLight : public PageBase
{
public:

public:
    CandleLight();
    virtual ~CandleLight();

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
    CandleLightView View;
    CandleLightModel Model;
};

}

#endif
