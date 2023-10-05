#include "LogicAnalyzerView.h"
#include <cstdio>

using namespace Page;


void LogicAnalyzerView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Panel1 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel1, 141);
    lv_obj_set_height(ui_Panel1, 100);
    lv_obj_set_x(ui_Panel1, 49);
    lv_obj_set_y(ui_Panel1, -49);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x212121), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_Panel1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Image2 = lv_img_create(root);
    lv_img_set_src(ui_Image2, ResourcePool::GetImage("sigrok_logo"));
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);  /// 100
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT); /// 100
    lv_obj_set_x(ui_Image2, -82);
    lv_obj_set_y(ui_Image2, -51);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ui_Label1 = lv_label_create(root);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label1, -2);
    lv_obj_set_y(ui_Label1, 35);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Logic Analyzer");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0x6200EE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, ResourcePool::GetFont("sf_compact_42"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label2 = lv_label_create(root);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label2, -82);
    lv_obj_set_y(ui_Label2, 80);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "ROW ONE");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x6CB6FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label3 = lv_label_create(root);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label3, -83);
    lv_obj_set_y(ui_Label3, 100);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "(TOP)");
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0xAE4C82), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Image3 = lv_img_create(root);
    lv_img_set_src(ui_Image3, ResourcePool::GetImage("pin_logicanalyzer"));
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);  /// 79
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT); /// 26
    lv_obj_set_x(ui_Image3, 54);
    lv_obj_set_y(ui_Image3, 96);
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE); /// Flags

}




void LogicAnalyzerView::Delete()
{
    printf("LogicAnalyzerView::Delete()\n");
}

