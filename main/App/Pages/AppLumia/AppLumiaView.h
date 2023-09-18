#ifndef __AppLumia_VIEW_H
#define __AppLumia_VIEW_H

#include "../Page.h"

namespace Page
{

class AppLumiaView
{
public:
    void Create(lv_obj_t* root);
    void Delete();
    void add_item(lv_obj_t *parent, char *name, const void *src, lv_event_cb_t callback);
    void create_tile(lv_obj_t *parent, char *name, const void *src, int col, int row, int size, lv_event_cb_t callback);

public:


public:

private:
};

}

#endif // !__VIEW_H
