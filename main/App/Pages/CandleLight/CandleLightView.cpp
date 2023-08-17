#include "CandleLightView.h"
#include <cstdio>

using namespace Page;


void CandleLightView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_IICAddress = lv_label_create(root);
    lv_obj_set_width(ui_IICAddress, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_IICAddress, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_IICAddress, -70);
    lv_obj_set_y(ui_IICAddress, -84);
    lv_obj_set_align(ui_IICAddress, LV_ALIGN_CENTER);
    lv_label_set_text(ui_IICAddress, "CAN");
    lv_obj_set_style_text_color(ui_IICAddress, lv_color_hex(0xF80505), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_IICAddress, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_IICAddress, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_BarScanProgess = lv_bar_create(root);
    lv_bar_set_value(ui_BarScanProgess, 25, LV_ANIM_OFF);
    lv_obj_set_width(ui_BarScanProgess, 206);
    lv_obj_set_height(ui_BarScanProgess, 10);
    lv_obj_set_x(ui_BarScanProgess, -3);
    lv_obj_set_y(ui_BarScanProgess, -46);
    lv_obj_set_align(ui_BarScanProgess, LV_ALIGN_CENTER);

    lv_obj_t *ui_Status = lv_label_create(root);
    lv_obj_set_width(ui_Status, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Status, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Status, 61);
    lv_obj_set_y(ui_Status, -83);
    lv_obj_set_align(ui_Status, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Status, "500000\n kbps\n CAN 2.0");
    lv_obj_set_style_text_color(ui_Status, lv_color_hex(0x06FD5A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Status, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_PinMapIMG = lv_img_create(root);
    lv_img_set_src(ui_PinMapIMG, ResourcePool::GetImage("pin_can"));
    lv_obj_set_width(ui_PinMapIMG, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_PinMapIMG, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_PinMapIMG, 17);
    lv_obj_set_y(ui_PinMapIMG, 105);
    lv_obj_set_align(ui_PinMapIMG, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PinMapIMG, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_PinMapIMG, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ui_LogScani2c = lv_textarea_create(root);
    lv_obj_set_width(ui_LogScani2c, 217);
    lv_obj_set_height(ui_LogScani2c, 117);
    lv_obj_set_x(ui_LogScani2c, -3);
    lv_obj_set_y(ui_LogScani2c, 28);
    lv_obj_set_align(ui_LogScani2c, LV_ALIGN_CENTER);
    lv_textarea_set_text(ui_LogScani2c, "0x52 found at 122.32s\n0x22 found at version qwfe\n");
    lv_textarea_set_placeholder_text(ui_LogScani2c, "Placeholder...");
}




void CandleLightView::Delete()
{
    printf("CandleLightView::Delete()");
}

