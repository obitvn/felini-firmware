#ifndef __PowerSupply_PRESENTER_H
#define __PowerSupply_PRESENTER_H

#include "PowerSupplyView.h"
#include "PowerSupplyModel.h"

namespace Page
{

class PowerSupply : public PageBase
{
public:
    typedef struct
    {
        uint16_t time;
        lv_color_t color;
    } Param_t;

public:
    PowerSupply();
    virtual ~PowerSupply();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

    virtual void settoDefault();
    virtual void onShow();

private:
    void Update();
    void AttachEvent(lv_obj_t* obj);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    PowerSupplyView View;
    PowerSupplyModel Model;
    lv_timer_t* timer;
};

}

#endif
