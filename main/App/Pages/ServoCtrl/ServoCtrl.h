#ifndef __ServoCtrl_PRESENTER_H
#define __ServoCtrl_PRESENTER_H

#include "ServoCtrlView.h"
#include "ServoCtrlModel.h"

namespace Page
{

class ServoCtrl : public PageBase
{
public:
    

public:
    ServoCtrl();
    virtual ~ServoCtrl();

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
    void AttachGesture(lv_obj_t *obj);
    void AttachEvent(lv_obj_t *obj);
    void ViewUpdatePos(lv_event_t *event);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    ServoCtrlView View;
    ServoCtrlModel Model;
};

}

#endif
