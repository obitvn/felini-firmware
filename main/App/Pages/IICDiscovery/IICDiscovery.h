#ifndef __IICDiscovery_PRESENTER_H
#define __IICDiscovery_PRESENTER_H

#include "IICDiscoveryView.h"
#include "IICDiscoveryModel.h"

namespace Page
{

class IICDiscovery : public PageBase
{
public:

public:
    IICDiscovery();
    virtual ~IICDiscovery();

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
    void Update(lv_timer_t *timer);
    static void onTimer(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

private:
    IICDiscoveryView View;
    IICDiscoveryModel Model;
    lv_timer_t *timer;
};

}

#endif
