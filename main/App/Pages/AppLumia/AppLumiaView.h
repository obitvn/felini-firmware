#ifndef __AppLumia_VIEW_H
#define __AppLumia_VIEW_H

#include "../Page.h"

namespace Page
{

class AppLumiaView
{

public:
    typedef struct
    {
        lv_obj_t *cont;
        lv_obj_t *btn_cell;
        lv_obj_t *btn;
        lv_obj_t *icon;
        lv_obj_t *labelInfo;
        lv_obj_t *labelData;
        const char *app_src;
    } item_t;

    struct
    {
        item_t analog;
        item_t ledcolor;
        item_t timekeeper;
        item_t i2cscan;
        item_t powerpd;
        item_t ccpmservo;
        item_t uartter;
        item_t daplink;
        item_t usbcanbus;
        item_t kaitokey;
        item_t frequency;
        item_t imu;
        item_t logicanalyzer;
    } ui;

public:
    void Create(lv_obj_t* root);
    void Delete();
    void CreateItemList(const char *app_src, lv_obj_t *parent, const char *name, const char *img_src, const char *infos, item_t *item);
    void CreateItemCell(const char *app_src, lv_obj_t *parent, const char *name, const char *img_src, int col, int row, int size, item_t *item);

public:


public:

private:
};

}

#endif // !__VIEW_H
