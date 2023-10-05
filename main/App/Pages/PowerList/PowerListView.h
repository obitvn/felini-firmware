#ifndef __PowerList_VIEW_H
#define __PowerList_VIEW_H

#include "../Page.h"

namespace Page
{

class PowerListView
{

public:
    typedef struct
    {
        lv_obj_t *cont;
        lv_obj_t *btn_cell;
        lv_obj_t *label;
        float     volt;
        bool state;
        uint32_t color;
    } item_t;

    struct
    {
        item_t item[64];
    } ui;

public:
    void Create(lv_obj_t* root);
    void Delete();
    void CreateItemCell(float voltage, lv_obj_t *parent, const char *name, uint32_t color,  int col, int row, int size);

public:


public:
public:
    uint32_t index_item;
    uint32_t index_col;
    uint32_t index_row;
};

}

#endif // !__VIEW_H
