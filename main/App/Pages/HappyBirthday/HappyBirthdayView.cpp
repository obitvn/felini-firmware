#include "HappyBirthdayView.h"
#include <cstdio>

using namespace Page;


void HappyBirthdayView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);


    lv_obj_t * ui_Image1 = lv_img_create(root);
    lv_img_set_src(ui_Image1, ResourcePool::GetImage("hpbd_png"));
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(ui_Image1, 128);
}




void HappyBirthdayView::Delete()
{
    printf("HappyBirthdayView::Delete()");
}

