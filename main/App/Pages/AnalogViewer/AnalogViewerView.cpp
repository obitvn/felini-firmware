#include "AnalogViewerView.h"
#include <cstdio>

using namespace Page;


void AnalogViewerView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Chart1 = lv_chart_create(root);
    ui.chart.cont = ui_Chart1;
    
    lv_obj_set_width(ui_Chart1, 216);
    lv_obj_set_height(ui_Chart1, 124);
    lv_obj_set_x(ui_Chart1, 3);
    lv_obj_set_y(ui_Chart1, 1);
    lv_obj_set_align(ui_Chart1, LV_ALIGN_CENTER);
    lv_obj_set_style_size(ui_Chart1, 0, LV_PART_INDICATOR); /*Hiển thị cả đường và điểm*/
    lv_chart_set_type(ui_Chart1, LV_CHART_TYPE_LINE); /*Không hiển thị điểm trên dữ liệu*/
    lv_chart_set_update_mode(ui_Chart1, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_range(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 0, 20);
    lv_chart_set_div_line_count(ui_Chart1, 0, 0);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_PRIMARY_Y, 10, 2, 3, 2, true, 50);
    lv_chart_set_axis_tick(ui_Chart1, LV_CHART_AXIS_SECONDARY_Y, 10, 5, 5, 2, false, 25);
    lv_chart_series_t *ui_Chart1_series_1 = lv_chart_add_series(ui_Chart1, lv_color_hex(0x079aff),
                                                                LV_CHART_AXIS_PRIMARY_Y);
    ui.chart.ser = ui_Chart1_series_1;


    lv_obj_t *ui_Label6 = lv_label_create(root);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label6, 120);
    lv_obj_set_y(ui_Label6, -82);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "V");
    lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0x42FC10), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label6, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label8 = lv_label_create(root);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label8, -1);
    lv_obj_set_y(ui_Label8, 100);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "connection to power out port");
    lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label8, &lv_font_montserrat_12, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label5 = lv_label_create(root);
    ui.label.cont = ui_Label5;
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, 42);
    lv_obj_set_y(ui_Label5, -91);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "00.000");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xFF6610), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label7 = lv_label_create(root);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label7, -83);
    lv_obj_set_y(ui_Label7, -91);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "ADC");
    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x08A3FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, &lv_font_montserrat_40, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel2 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel2, 2);
    lv_obj_set_height(ui_Panel2, 42);
    lv_obj_set_x(ui_Panel2, -29);
    lv_obj_set_y(ui_Panel2, -91);
    lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x0BF429), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x0BF429), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
}




void AnalogViewerView::Delete()
{
    printf("AnalogViewerView::Delete()");
}

