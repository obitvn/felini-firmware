#ifndef __HappyBirthday_PRESENTER_H
#define __HappyBirthday_PRESENTER_H

#include "HappyBirthdayView.h"
#include "HappyBirthdayModel.h"

namespace Page
{

class HappyBirthday : public PageBase
{
public:

public:
    HappyBirthday();
    virtual ~HappyBirthday();

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
    HappyBirthdayView View;
    HappyBirthdayModel Model;
};

}

#endif
