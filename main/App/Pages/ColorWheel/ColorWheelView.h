#ifndef __ColorWheel_VIEW_H
#define __ColorWheel_VIEW_H

#include "../Page.h"

namespace Page
{

class ColorWheelView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
public:
    typedef struct
    {
        lv_obj_t *cont;
        const char *name;
    } item_t;

    struct
    {
        item_t color;
    } ui;

private:
};

}

#endif // !__VIEW_H
