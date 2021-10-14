#ifndef __STARTUP_PRESENTER_H
#define __STARTUP_PRESENTER_H

#include "StartupView.h"
#include "StartupModel.h"

namespace Page
{

class Startup : public PageBase
{
public:

public:
    Startup();
    virtual ~Startup();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewDidUnload();

private:
    static void onTimer(lv_timer_t* timer);

    StartupView View;
    StartupModel Model;
};

}

#endif
