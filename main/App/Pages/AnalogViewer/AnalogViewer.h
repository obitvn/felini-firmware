#ifndef __AnalogViewer_PRESENTER_H
#define __AnalogViewer_PRESENTER_H

#include "AnalogViewerView.h"
#include "AnalogViewerModel.h"

namespace Page
{

class AnalogViewer : public PageBase
{
public:

public:
    AnalogViewer();
    virtual ~AnalogViewer();

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
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    AnalogViewerView View;
    AnalogViewerModel Model;

private:
    lv_timer_t *timer;
};

}

#endif
