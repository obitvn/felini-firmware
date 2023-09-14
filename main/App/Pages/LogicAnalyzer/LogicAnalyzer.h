#ifndef __LogicAnalyzer_PRESENTER_H
#define __LogicAnalyzer_PRESENTER_H

#include "LogicAnalyzerView.h"
#include "LogicAnalyzerModel.h"

namespace Page
{

class LogicAnalyzer : public PageBase
{
public:

public:
    LogicAnalyzer();
    virtual ~LogicAnalyzer();

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
    LogicAnalyzerView View;
    LogicAnalyzerModel Model;
};

}

#endif
