#include "HertzView.h"
#include <cstdio>

using namespace Page;


void HertzView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Label1 = lv_label_create(root);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label1, -46);
    lv_obj_set_y(ui_Label1, -62);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "192");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0x4284E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, ResourcePool::GetFont("sf_compact_72"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label2 = lv_label_create(root);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label2, 81);
    lv_obj_set_y(ui_Label2, -77);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "KHz");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x4284E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, ResourcePool::GetFont("sf_compact_36"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label3 = lv_label_create(root);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label3, -78);
    lv_obj_set_y(ui_Label3, 47);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "5.2");
    lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0x4284E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label3, ResourcePool::GetFont("sf_compact_34"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label4 = lv_label_create(root);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label4, -66);
    lv_obj_set_y(ui_Label4, 5);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "EDGE");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0x986EE2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel1 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel1, 217);
    lv_obj_set_height(ui_Panel1, 5);
    lv_obj_set_x(ui_Panel1, 0);
    lv_obj_set_y(ui_Panel1, -21);
    lv_obj_set_align(ui_Panel1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0xE5534B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // lv_obj_t *ui_Panel2 = lv_obj_create(root);
    // lv_obj_set_width(ui_Panel2, 5);
    // lv_obj_set_height(ui_Panel2, 76);
    // lv_obj_set_x(ui_Panel2, 0);
    // lv_obj_set_y(ui_Panel2, 27);
    // lv_obj_set_align(ui_Panel2, LV_ALIGN_CENTER);
    // lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    // lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0xAD2E2B), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label5 = lv_label_create(root);
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, -32);
    lv_obj_set_y(ui_Label5, 51);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "nS");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0x316DCA), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, ResourcePool::GetFont("sf_compact_20"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label6 = lv_label_create(root);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label6, 60);
    lv_obj_set_y(ui_Label6, 6);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "DUTY");
    lv_obj_set_style_text_color(ui_Label6, lv_color_hex(0xAE7C13), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label6, ResourcePool::GetFont("sf_compact_26"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label7 = lv_label_create(root);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label7, 49);
    lv_obj_set_y(ui_Label7, 47);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "75");
    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x46954A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, ResourcePool::GetFont("sf_compact_34"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label8 = lv_label_create(root);
    lv_obj_set_width(ui_Label8, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label8, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label8, 88);
    lv_obj_set_y(ui_Label8, 50);
    lv_obj_set_align(ui_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label8, "%");
    lv_obj_set_style_text_color(ui_Label8, lv_color_hex(0x347D39), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label8, ResourcePool::GetFont("sf_compact_20"), LV_PART_MAIN | LV_STATE_DEFAULT);
}




void HertzView::Delete()
{
    printf("HertzView::Delete()\n");
}

