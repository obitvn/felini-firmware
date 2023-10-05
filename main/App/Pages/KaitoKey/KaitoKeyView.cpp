#include "KaitoKeyView.h"
#include <cstdio>

using namespace Page;


void KaitoKeyView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Image9 = lv_img_create(root);
    lv_img_set_src(ui_Image9, ResourcePool::GetImage("chutienthinh"));
    lv_obj_set_width(ui_Image9, LV_SIZE_CONTENT);  /// 330
    lv_obj_set_height(ui_Image9, LV_SIZE_CONTENT); /// 240
    lv_obj_set_x(ui_Image9, -4);
    lv_obj_set_y(ui_Image9, 0);
    lv_obj_set_align(ui_Image9, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image9, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image9, LV_OBJ_FLAG_SCROLLABLE); /// Flags
}




void KaitoKeyView::Delete()
{
    printf("KaitoKeyView::Delete()\n");
}

