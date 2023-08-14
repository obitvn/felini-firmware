#include "AnalogViewerView.h"
#include <cstdio>

using namespace Page;


void AnalogViewerView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_AppLabel = lv_label_create(root);
    lv_obj_set_width(ui_AppLabel, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_AppLabel, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_AppLabel, -72);
    lv_obj_set_y(ui_AppLabel, -89);
    lv_obj_set_align(ui_AppLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AppLabel, "12.3V");
    lv_obj_set_style_text_color(ui_AppLabel, lv_color_hex(0x02DBF8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_AppLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_AppLabel, ResourcePool::GetFont("alibabasans_regular_48"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_VoltMax = lv_label_create(root);
    lv_obj_set_width(ui_VoltMax, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_VoltMax, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_VoltMax, 36);
    lv_obj_set_y(ui_VoltMax, -101);
    lv_obj_set_align(ui_VoltMax, LV_ALIGN_CENTER);
    lv_label_set_text(ui_VoltMax, "Analog");
    lv_obj_set_style_text_color(ui_VoltMax, lv_color_hex(0xFB0A0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_VoltMax, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_VoltMax, ResourcePool::GetFont("alibabasans_regular_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_VoltRealTime = lv_label_create(root);
    lv_obj_set_width(ui_VoltRealTime, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_VoltRealTime, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_VoltRealTime, 36);
    lv_obj_set_y(ui_VoltRealTime, -74);
    lv_obj_set_align(ui_VoltRealTime, LV_ALIGN_CENTER);
    lv_label_set_text(ui_VoltRealTime, "10.145 mV");
    lv_obj_set_style_text_color(ui_VoltRealTime, lv_color_hex(0x27FB0A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_VoltRealTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_VoltRealTime, ResourcePool::GetFont("alibabasans_regular_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_VoltChart = lv_obj_create(root);
    lv_obj_set_width(ui_VoltChart, 257);
    lv_obj_set_height(ui_VoltChart, 132);
    lv_obj_set_x(ui_VoltChart, -1);
    lv_obj_set_y(ui_VoltChart, 10);
    lv_obj_set_align(ui_VoltChart, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_VoltChart, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_VoltChart, lv_color_hex(0x090909), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_VoltChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_VoltChart, lv_color_hex(0x0FEFF3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_VoltChart, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Pinmapvolt = lv_img_create(root);
    lv_img_set_src(ui_Pinmapvolt, ResourcePool::GetImage("sd_card"));
    lv_obj_set_width(ui_Pinmapvolt, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Pinmapvolt, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Pinmapvolt, -1);
    lv_obj_set_y(ui_Pinmapvolt, 104);
    lv_obj_set_align(ui_Pinmapvolt, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Pinmapvolt, LV_OBJ_FLAG_ADV_HITTEST);
}




void AnalogViewerView::Delete()
{
    printf("AnalogViewerView::Delete()");
}

