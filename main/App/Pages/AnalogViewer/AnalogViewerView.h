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
        lv_obj_t *cont;
        lv_chart_series_t *ser;
        const char *name;
    } item_t;

    struct
    {
        item_t label;
        item_t chart;
    } ui;

public:

private:
};

}

#endif // !__VIEW_H
