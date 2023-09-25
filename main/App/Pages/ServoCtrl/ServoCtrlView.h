#ifndef __ServoCtrl_VIEW_H
#define __ServoCtrl_VIEW_H

#include "../Page.h"

namespace Page
{

class ServoCtrlView
{
public:
    void Create(lv_obj_t* root);
    void Delete();
    

public:
    typedef struct
    {
        lv_obj_t *cont;
        const char *name;
    } item_t;

    struct
    {
        item_t arc;
        item_t angle;
        item_t spin;
    } ui;

public:

private:
};

}

#endif // !__VIEW_H
