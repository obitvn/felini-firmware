#include "IntervalView.h"
#include <cstdio>

using namespace Page;


void IntervalView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Panel7 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel7, 280);
    lv_obj_set_height(ui_Panel7, 40);
    lv_obj_set_x(ui_Panel7, 0);
    lv_obj_set_y(ui_Panel7, -100);
    lv_obj_set_align(ui_Panel7, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel7, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_Panel7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel7, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel2 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel2, 290);
    lv_obj_set_height(ui_Panel2, 40);
    lv_obj_set_x(ui_Panel2, 0);
    lv_obj_set_y(ui_Panel2, 100);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_radius(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label11 = lv_label_create(root);
    lv_obj_set_width(ui_Label11, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label11, LV_SIZE_CONTENT); /// 1
    lv_obj_set_align(ui_Label11, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Label11, "Frequency");
    lv_obj_set_x(ui_Label11, 0);
    lv_obj_set_y(ui_Label11, -102);
    lv_obj_set_align(ui_Label11, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_Label11, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label11, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label11, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label10 = lv_label_create(root);
    ui.freq.cont = ui_Label10;
    lv_obj_set_width(ui_Label10, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label10, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label10, 0);
    lv_obj_set_y(ui_Label10, -25);
    lv_obj_set_align(ui_Label10, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label10, "0");
    lv_obj_set_style_text_color(ui_Label10, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label10, ResourcePool::GetFont("sf_compact_72"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label12 = lv_label_create(root);
    lv_obj_set_width(ui_Label12, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label12, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label12, -97+10);
    lv_obj_set_y(ui_Label12, 92);
    lv_obj_set_align(ui_Label12, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label12, "ROW TWO");
    lv_obj_set_style_text_color(ui_Label12, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label12, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label13 = lv_label_create(root);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label13, -101+10);
    lv_obj_set_y(ui_Label13, 108);
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label13, "(BOT)");
    lv_obj_set_style_text_color(ui_Label13, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label13, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label13, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label14 = lv_label_create(root);
    ui.unit.cont = ui_Label14;
    lv_obj_set_width(ui_Label14, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label14, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label14, 86);
    lv_obj_set_y(ui_Label14, 27);
    lv_obj_set_align(ui_Label14, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label14, "kHz");
    lv_obj_set_style_text_color(ui_Label14, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label14, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label14, ResourcePool::GetFont("sf_compact_22"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label15 = lv_label_create(root);
    ui.time.cont = ui_Label15;
    lv_obj_set_width(ui_Label15, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label15, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label15, -48);
    lv_obj_set_y(ui_Label15, 27);
    lv_obj_set_align(ui_Label15, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label15, "0 pS");
    lv_obj_set_style_text_color(ui_Label15, lv_color_hex(0x7E52CC), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label15, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label15, ResourcePool::GetFont("sf_compact_22"), LV_PART_MAIN | LV_STATE_DEFAULT);

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




void IntervalView::Delete()
{
    printf("IntervalView::Delete()\n");
}

