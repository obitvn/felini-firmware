#ifndef __KaitoKey_PRESENTER_H
#define __KaitoKey_PRESENTER_H

#include "KaitoKeyView.h"
#include "KaitoKeyModel.h"

namespace Page
{

class KaitoKey : public PageBase
{
public:

public:
    KaitoKey();
    virtual ~KaitoKey();

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
    KaitoKeyView View;
    KaitoKeyModel Model;
};

}

#endif
