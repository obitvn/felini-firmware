#include "ColorWheelView.h"
#include <cstdio>

using namespace Page;

// counting number of lec ws2812???

void ColorWheelView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Colorwheel1 = lv_colorwheel_create(root, true);
    ui.color.cont = ui_Colorwheel1;
    lv_obj_set_width(ui_Colorwheel1, 160);
    lv_obj_set_height(ui_Colorwheel1, 160);
    lv_obj_set_x(ui_Colorwheel1, 0);
    lv_obj_set_y(ui_Colorwheel1, -15);
    lv_obj_set_align(ui_Colorwheel1, LV_ALIGN_CENTER);
    

    lv_obj_t *ui_LabelAPP = lv_label_create(root);
    lv_obj_set_width(ui_LabelAPP, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LabelAPP, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LabelAPP, -3);
    lv_obj_set_y(ui_LabelAPP, -21);
    lv_obj_set_align(ui_LabelAPP, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAPP, "LED");
    lv_obj_set_style_text_color(ui_LabelAPP, lv_color_hex(0x079EFB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAPP, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelAPP, ResourcePool::GetFont("sf_compact_48"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_LabelAppTag = lv_label_create(root);
    lv_obj_set_width(ui_LabelAppTag, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LabelAppTag, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LabelAppTag, -2);
    lv_obj_set_y(ui_LabelAppTag, 14);
    lv_obj_set_align(ui_LabelAppTag, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelAppTag, "ColorWheel");
    lv_obj_set_style_text_color(ui_LabelAppTag, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelAppTag, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Pinmap = lv_img_create(root);
    lv_img_set_src(ui_Pinmap, ResourcePool::GetImage("pin_color_wheel"));
    lv_obj_set_width(ui_Pinmap, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Pinmap, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Pinmap, 82);
    lv_obj_set_y(ui_Pinmap, 97);
    lv_obj_set_align(ui_Pinmap, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Pinmap, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Pinmap, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ui_MapPos = lv_label_create(root);
    lv_obj_set_width(ui_MapPos, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_MapPos, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_MapPos, -99);
    lv_obj_set_y(ui_MapPos, 75);
    lv_obj_set_align(ui_MapPos, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MapPos, "ROW1");
    lv_obj_set_style_text_color(ui_MapPos, lv_color_hex(0xFBFBFB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MapPos, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_LabelPin = lv_label_create(root);
    lv_obj_set_width(ui_LabelPin, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LabelPin, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LabelPin, -80);
    lv_obj_set_y(ui_LabelPin, 101);
    lv_obj_set_align(ui_LabelPin, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelPin, "LED DATA pin");
    lv_obj_set_style_text_color(ui_LabelPin, lv_color_hex(0xFDFDFD), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelPin, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelPin, ResourcePool::GetFont("sf_compact_14"), LV_PART_MAIN | LV_STATE_DEFAULT);
}




void ColorWheelView::Delete()
{
    printf("ColorWheelView::Delete()\n");
}

