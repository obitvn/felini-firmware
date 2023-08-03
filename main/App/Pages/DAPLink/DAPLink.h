#ifndef __DAPLink_PRESENTER_H
#define __DAPLink_PRESENTER_H

#include "DAPLinkView.h"
#include "DAPLinkModel.h"

namespace Page
{

class DAPLink : public PageBase
{
public:

public:
    DAPLink();
    virtual ~DAPLink();

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
    void enableHW(int value);

private:
    DAPLinkView View;
    DAPLinkModel Model;
};

}

#endif
