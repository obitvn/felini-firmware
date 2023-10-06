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
    ui.panel.cont = ui_Panel4;
    lv_obj_set_width(ui_Panel4, 135);
    lv_obj_set_height(ui_Panel4, 115);
    lv_obj_set_x(ui_Panel4, 60);
    lv_obj_set_y(ui_Panel4, 0);
    lv_obj_set_align(ui_Panel4, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_Panel4, ResourcePool::GetImage("pulsechart"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label4 = lv_label_create(root);
    ui.frequency.cont = ui_Label4;
    ui.frequency.value = 0;
    ui.frequency.state - false;
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label4, -79);
    lv_obj_set_y(ui_Label4, -38);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "000.00");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label5 = lv_label_create(root);
    ui.unit.cont = ui_Label5;
    ui.unit.btn = ui_Label5;
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, -40);
    lv_obj_set_y(ui_Label5, -12);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Khz");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label6 = lv_label_create(root);
    ui.duty.cont = ui_Label6;
    ui.duty.value = 0;
    ui.duty.state = false;
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label6, -101);
    lv_obj_set_y(ui_Label6, 44);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "0%");
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
    lv_label_set_text(ui_Label12, "ROW TWO");
    lv_obj_set_style_text_color(ui_Label12, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label12, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label12, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label13 = lv_label_create(root);
    lv_obj_set_width(ui_Label13, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label13, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label13, -101 + 10);
    lv_obj_set_y(ui_Label13, 108);
    lv_obj_set_align(ui_Label13, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label13, "(BOT)");
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

    lv_obj_t *ui_Button2 = lv_btn_create(root);
    ui.frequency.btn = ui_Button2;
    lv_obj_remove_style_all(ui_Button2);
    lv_obj_set_style_radius(ui_Button2, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(ui_Button2, 116);
    lv_obj_set_height(ui_Button2, 64);
    lv_obj_set_x(ui_Button2, -79);
    lv_obj_set_y(ui_Button2, -31);
    lv_obj_set_align(ui_Button2, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Button2, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_Button2, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_Button2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button2, 50, LV_PART_MAIN | LV_STATE_PRESSED);
    // lv_obj_set_style_bg_opa(ui_Button2, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_t *ui_Button1 = lv_btn_create(root);
    ui.duty.btn = ui_Button1;
    lv_obj_remove_style_all(ui_Button1);
    lv_obj_set_style_radius(ui_Button1, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(ui_Button1, 116);
    lv_obj_set_height(ui_Button1, 64);
    lv_obj_set_x(ui_Button1, -79);
    lv_obj_set_y(ui_Button1, 39);
    lv_obj_set_align(ui_Button1, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Button1, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_Button1, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_Button1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button1, 50, LV_PART_MAIN | LV_STATE_PRESSED);
    // lv_obj_set_style_bg_opa(ui_Button1, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_t *ui_Button3 = lv_btn_create(root);
    ui.panel.btn = ui_Button3;
    lv_obj_remove_style_all(ui_Button3);
    lv_obj_set_style_radius(ui_Button3, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(ui_Button3, 135);
    lv_obj_set_height(ui_Button3, 115);
    lv_obj_set_x(ui_Button3, 60);
    lv_obj_set_y(ui_Button3, 0);
    lv_obj_set_align(ui_Button3, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_Button3, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_Button3, lv_color_hex(0xff0000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button3, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Button3, 50, LV_PART_MAIN | LV_STATE_PRESSED);
    // lv_obj_set_style_bg_opa(ui_Button3, 50, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_t *spinbox = lv_spinbox_create(root);
    lv_obj_remove_style_all(spinbox);
    lv_obj_set_x(spinbox, 320);
    lv_obj_set_y(spinbox, 320);
    lv_spinbox_set_cursor_pos(spinbox, 7);
    lv_spinbox_set_digit_format(spinbox, 7, 0);
    lv_spinbox_set_range(spinbox, 0, 8000000);
    lv_spinbox_set_step(spinbox, 1);
    ui.spin.btn = spinbox;
    ui.spin.cont = spinbox;

}




void HertzView::Delete()
{
    printf("HertzView::Delete()\n");
}

