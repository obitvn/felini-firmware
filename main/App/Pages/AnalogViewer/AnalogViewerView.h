#ifndef __AnalogViewer_VIEW_H
#define __AnalogViewer_VIEW_H

#include "../Page.h"

namespace Page
{

class AnalogViewerView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t *set;
        lv_obj_t *button;
        lv_obj_t *label;
        const char *name;
    } item_t;

    struct
    {
        item_t voltage;
        item_t current;
        item_t power;
        // item_t confirm;
        // item_t slider;
        item_t spin;
    } ui;

public:

private:
};

}

#endif // !__VIEW_H
