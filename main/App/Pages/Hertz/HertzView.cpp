#include "HertzView.h"
#include <cstdio>

using namespace Page;


void HertzView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Label1 = lv_label_create(root);
    lv_obj_t *ui_Panel7 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel7, 280);
    lv_obj_set_height(ui_Panel7, 40);
    lv_obj_set_x(ui_Panel7, 0);
    lv_obj_set_y(ui_Panel7, -100);
    lv_obj_set_align(ui_Panel7, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel7, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_Panel7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel7, lv_color_hex(0x22beaa), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel2 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel2, 280);
    lv_obj_set_height(ui_Panel2, 40);
    lv_obj_set_x(ui_Panel2, 0);
    lv_obj_set_y(ui_Panel2, 100);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x22beaa), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel4 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel4, 135);
    lv_obj_set_height(ui_Panel4, 115);
    lv_obj_set_x(ui_Panel4, 60);
    lv_obj_set_y(ui_Panel4, 0);
    lv_obj_set_align(ui_Panel4, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_Panel4, ResourcePool::GetImage("pulsechart"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label4 = lv_label_create(root);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label4, -79);
    lv_obj_set_y(ui_Label4, -38);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "982.46");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label5 = lv_label_create(root);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, -40);
    lv_obj_set_y(ui_Label5, -12);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Khz");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label6 = lv_label_create(root);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label6, -101);
    lv_obj_set_y(ui_Label6, 44);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "75%");
    lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0x8E2DA1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label6, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label7 = lv_label_create(root);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label7, -40);
    lv_obj_set_y(ui_Label7, 49);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "duty");
    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x8E2DA1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label11 = lv_label_create(root);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_Label11, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label11, "Signal Generator");
    lv_obj_set_x(ui_Label11, 0);
    lv_obj_set_y(ui_Label11, -102);
    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_Label11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label11, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label12 = lv_label_create(root);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label12, -97 + 10);
    lv_obj_set_y(ui_Label12, 92);
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "ROW ONE");
    lv_obj_set_style_text_color(ui_Label12, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label12, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label13 = lv_label_create(root);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label13, -101 + 10);
    lv_obj_set_y(ui_Label13, 108);
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label13, "(TOP)");
    lv_obj_set_style_text_color(ui_Label13, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label13, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Image6 = lv_img_create(root);
    lv_img_set_src(ui_Image6, ResourcePool::GetImage("pin_pulse"));
    lv_obj_set_width(ui_Image6, LV_SIZE_CONTENT);  /// 50
    lv_obj_set_height(ui_Image6, LV_SIZE_CONTENT); /// 34
    lv_obj_set_x(ui_Image6, 94);
    lv_obj_set_y(ui_Image6, 102);
    lv_obj_set_align(ui_Image6, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image6, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image6, LV_OBJ_FLAG_SCROLLABLE); /// Flags
}




void HertzView::Delete()
{
    printf("HertzView::Delete()\n");
}

