#ifndef __UARTViewer_VIEW_H
#define __UARTViewer_VIEW_H

#include "../Page.h"

namespace Page
{

class UARTViewerView
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
        item_t text;
        item_t keyboard;
        item_t baud;
    } ui;

private:
};

}

#endif // !__VIEW_H
