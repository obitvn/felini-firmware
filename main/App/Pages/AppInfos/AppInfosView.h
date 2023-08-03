#ifndef __SYSTEM_INFOS_VIEW_H
#define __SYSTEM_INFOS_VIEW_H

#include "../Page.h"

namespace Page
{

class AppInfosView
{
public:
    void Create(lv_obj_t* root);
    void Delete();

public:
    typedef struct
    {
        lv_obj_t* cont;
        lv_obj_t* icon;
        lv_obj_t* labelInfo;
        lv_obj_t* labelData;
        const char *app_src;
    } item_t;

    struct
    {
        item_t sport;
        item_t gps;
        item_t mag;
        item_t imu;
        item_t rtc;
        item_t battery;
        item_t storage;
        item_t system;
    } ui;

public:

    void SetScrollToY(lv_obj_t* obj, lv_coord_t y, lv_anim_enable_t en);
    static void onFocus(lv_group_t* e);

private:
    struct
    {
        lv_style_t icon;
        lv_style_t focus;
        lv_style_t info;
        lv_style_t data;
    } style;

private:
    void Group_Init();
    void Style_Init();
    void Style_Reset();
    void Item_Create(
        const char *app_src,
        item_t * item,
        lv_obj_t *par,
        const char *name,
        const char *img_src,
        const char *infos);
};

}

#endif // !__VIEW_H
