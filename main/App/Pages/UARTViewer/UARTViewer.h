#ifndef __UARTViewer_PRESENTER_H
#define __UARTViewer_PRESENTER_H

#include "UARTViewerView.h"
#include "UARTViewerModel.h"

namespace Page
{

class UARTViewer : public PageBase
{
public:

public:
    UARTViewer();
    virtual ~UARTViewer();

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
    UARTViewerView View;
    UARTViewerModel Model;

private:
    lv_timer_t *timer;
    char text_buf[2048];
};

}

#endif
