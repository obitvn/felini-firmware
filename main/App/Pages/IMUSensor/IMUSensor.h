#ifndef __IMUSensor_PRESENTER_H
#define __IMUSensor_PRESENTER_H

#include "IMUSensorView.h"
#include "IMUSensorModel.h"

namespace Page
{

class IMUSensor : public PageBase
{
public:

public:
    IMUSensor();
    virtual ~IMUSensor();

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
    IMUSensorView View;
    IMUSensorModel Model;
};

}

#endif
