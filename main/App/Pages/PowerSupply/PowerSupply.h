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
    typedef struct
    {
        /* data */
        bool btn_state;
        uint16_t value;
    } item_state;
    
    item_state volt;
    item_state current;
    item_state power;
    item_state confirm;

private:

};

}

#endif
