#ifndef __Dialplate_VIEW_H
#define __Dialplate_VIEW_H

#include "../Page.h"

namespace Page
{

class DialplateView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t *cont;
        lv_obj_t *icon;
        lv_obj_t *labelInfo;
        const char *app_src;
    } item_t;

    typedef struct
    {
        item_t setting;
        item_t uart;
        item_t iic;
        item_t spi;
        item_t a;
        item_t b;
        item_t c;
        item_t d;
        item_t e;
        item_t f;
        item_t g;
        item_t h;
        item_t i;
        item_t k;
    } ui_t;

public:
    item_t scroll_panel;
    ui_t ui;
    void Item_Create(item_t *item, lv_obj_t *par, const char *name, const void *img_src, const char *app_src);
    void UpdatePosItem(lv_obj_t *cont);

private:
};

}

#endif // !__VIEW_H
