#ifndef __IICDiscovery_VIEW_H
#define __IICDiscovery_VIEW_H

#include "../Page.h"

namespace Page
{

class IICDiscoveryView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t *cont;
        lv_obj_t *label;
        const char *name;
    } item_t;

    struct
    {
        item_t addr;
        item_t status;
        item_t bar;
        item_t terminal;
    } ui;

public:

private:
};

}

#endif // !__VIEW_H
