#ifndef __Interval_VIEW_H
#define __Interval_VIEW_H

#include "../Page.h"

namespace Page
{

class IntervalView
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
        item_t freq;
    } ui;

public:

private:
};

}

#endif // !__VIEW_H
