#ifndef __MenuList_VIEW_H
#define __MenuList_VIEW_H

#include "../Page.h"

namespace Page
{

    class MenuListView
    {
    public:
        void Create(lv_obj_t *root);
        void Delete();
        void ShowControlPanel();
        void SetDefaultControlPanel();

        public : struct
        {
            lv_obj_t *back;
            lv_obj_t *list_menu;
            lv_obj_t *home;
            lv_obj_t *settings;
            lv_obj_t *remove;
            lv_obj_t *control;
            lv_obj_t *controlpanel;
        } ui;

    private:
        lv_obj_t *Btn_Create(lv_obj_t *par, const void *img_src, lv_coord_t x_ofs, lv_coord_t y_ofs);
    };

}

#endif // !__VIEW_H
