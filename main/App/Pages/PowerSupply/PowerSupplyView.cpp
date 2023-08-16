#include "PowerSupplyView.h"
#include <cstdio>

using namespace Page;


void PowerSupplyView::Create(lv_obj_t *root)
{
    /*Change the active screen's background color*/
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_VoltMeasure = lv_label_create(root);
    lv_obj_set_width(ui_VoltMeasure, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_VoltMeasure, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_VoltMeasure, -67);
    lv_obj_set_y(ui_VoltMeasure, -58);
    lv_obj_set_align(ui_VoltMeasure, LV_ALIGN_CENTER);
    lv_label_set_text(ui_VoltMeasure, "15.21");
    lv_obj_set_style_text_color(ui_VoltMeasure, lv_color_hex(0xFF1055), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_VoltMeasure, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_VoltMeasure, ResourcePool::GetFont("sf_compact_48"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_AmpMeasure = lv_label_create(root);
    lv_obj_set_width(ui_AmpMeasure, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AmpMeasure, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AmpMeasure, -63);
    lv_obj_set_y(ui_AmpMeasure, -1);
    lv_obj_set_align(ui_AmpMeasure, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AmpMeasure, "12.48");
    lv_obj_set_style_text_color(ui_AmpMeasure, lv_color_hex(0x9EFF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_AmpMeasure, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_AmpMeasure, ResourcePool::GetFont("sf_compact_48"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_PowerConsumer = lv_label_create(root);
    lv_obj_set_width(ui_PowerConsumer, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PowerConsumer, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PowerConsumer, -2);
    lv_obj_set_y(ui_PowerConsumer, 70);
    lv_obj_set_align(ui_PowerConsumer, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PowerConsumer, "12.48 W");
    lv_obj_set_style_text_color(ui_PowerConsumer, lv_color_hex(0x5BC8F8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_PowerConsumer, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_PowerConsumer, ResourcePool::GetFont("sf_compact_48"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_VoltSet = lv_label_create(root);
    lv_obj_set_width(ui_VoltSet, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_VoltSet, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_VoltSet, 61);
    lv_obj_set_y(ui_VoltSet, -56);
    lv_obj_set_align(ui_VoltSet, LV_ALIGN_CENTER);
    lv_label_set_text(ui_VoltSet, "/ 16.18V");
    lv_obj_set_style_text_color(ui_VoltSet, lv_color_hex(0xF20EB2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_VoltSet, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_VoltSet, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_AmpSet = lv_label_create(root);
    lv_obj_set_width(ui_AmpSet, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_AmpSet, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_AmpSet, 65);
    lv_obj_set_y(ui_AmpSet, -3);
    lv_obj_set_align(ui_AmpSet, LV_ALIGN_CENTER);
    lv_label_set_text(ui_AmpSet, "/ 3.48 A");
    lv_obj_set_style_text_color(ui_AmpSet, lv_color_hex(0xD2F20E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_AmpSet, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_AmpSet, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_PDmode = lv_label_create(root);
    lv_obj_set_width(ui_PDmode, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_PDmode, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_PDmode, -106);
    lv_obj_set_y(ui_PDmode, -100);
    lv_obj_set_align(ui_PDmode, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PDmode, "PPS");
    lv_obj_set_style_text_color(ui_PDmode, lv_color_hex(0x7FF547), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_PDmode, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_PDmode, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_temp = lv_label_create(root);
    lv_obj_set_width(ui_temp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_temp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_temp, -53);
    lv_obj_set_y(ui_temp, -100);
    lv_obj_set_align(ui_temp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_temp, "32*C");
    lv_obj_set_style_text_color(ui_temp, lv_color_hex(0xF0C016), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_temp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_temp, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_time = lv_label_create(root);
    lv_obj_set_width(ui_time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_time, 51);
    lv_obj_set_y(ui_time, -99);
    lv_obj_set_align(ui_time, LV_ALIGN_CENTER);
    lv_label_set_text(ui_time, "02:21:23");
    lv_obj_set_style_text_color(ui_time, lv_color_hex(0x1990A0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_time, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_time, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_poweron = lv_obj_create(root);
    lv_obj_set_width(ui_poweron, 20);
    lv_obj_set_height(ui_poweron, 20);
    lv_obj_set_x(ui_poweron, 121);
    lv_obj_set_y(ui_poweron, -97);
    lv_obj_set_align(ui_poweron, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_poweron, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_poweron, lv_color_hex(0x71F907), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_poweron, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_poweron, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}




void PowerSupplyView::Delete()
{
    printf("PowerSupplyView::Delete()");
}

