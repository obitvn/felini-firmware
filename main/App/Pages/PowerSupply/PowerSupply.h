#ifndef __PowerSupply_PRESENTER_H
#define __PowerSupply_PRESENTER_H

#include "PowerSupplyView.h"
#include "PowerSupplyModel.h"

namespace Page
{

class PowerSupply : public PageBase
{
public:

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

private:
    void Update();
    void AttachEvent(lv_obj_t *obj);
    void ViewUpdatePos(lv_event_t *event);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    PowerSupplyView View;
    PowerSupplyModel Model;


private:
    bool btn_volt_state;
    bool btn_current_state;
    bool btn_power_state;
    bool btn_confirm_state;

private:

};

}

#endif
