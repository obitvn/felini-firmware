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
    void Update(lv_timer_t *timer);
    void AttachEvent(lv_obj_t *obj);
    void ViewUpdatePos(lv_event_t *event);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    PowerSupplyView View;
    PowerSupplyModel Model;


private:
    typedef enum
    {
        PD_SET_RELEASED = 0,
        PD_SET_VOLT = 1,
        PD_SET_CURRENT = 2,
        PD_SET_CONFIRM = 3,
        PD_SET_POWER_OFF = 4,
        PD_SET_POWER_ON = 5
    } setup_state_t;

    typedef enum
    {
        PD_STEP_RELEASED    = 0,
        PD_STEP_10          = 10,
        PD_STEP_50          = 50,
        PD_STEP_100         = 100,
        PD_STEP_1000        = 1000
    } step_div_t;

    typedef struct
    {
        /* data */
        setup_state_t status;
        uint16_t value;
    } item_set_state;

    typedef struct
    {
        /* data */
        uint8_t btn_state;
        uint16_t value;
        uint16_t minval;
        uint16_t maxval;
        uint16_t step;
        int div;
    } item_state;
    
    item_set_state config;

    item_state volt;
    item_state current;
    item_state power;
    item_state confirm;


    lv_timer_t *timer;

private:

};

}

#endif
