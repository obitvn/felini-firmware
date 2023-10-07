#ifndef __Hertz_VIEW_H
#define __Hertz_VIEW_H

#include "../Page.h"

namespace Page
{

class HertzView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t *cont;
        float value;
        bool state;
    } item_t;

    struct
    {
        item_t frequency;
        item_t unit;
        item_t duty;
    } ui;

public:
private:
};

}

#endif // !__VIEW_H
