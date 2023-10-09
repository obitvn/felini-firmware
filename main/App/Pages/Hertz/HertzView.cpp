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
    // lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE); /// Flags// lv_obj_clear_flag(ui_Panel4, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_img_src(ui_Panel4, ResourcePool::GetImage("pulsechart"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *panel_btn = lv_btn_create(root);
    lv_obj_remove_style_all(panel_btn);
    lv_obj_set_width(panel_btn, 135);
    lv_obj_set_height(panel_btn, 115);
    lv_obj_set_x(panel_btn, 60);
    lv_obj_set_y(panel_btn, 0);
    lv_obj_set_align(panel_btn, LV_ALIGN_CENTER);
    lv_obj_set_style_bg_color(panel_btn, lv_color_hex(0x22beaa), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(panel_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(panel_btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(panel_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(panel_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(panel_btn, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(panel_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(panel_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(panel_btn, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *freq_spinbox = lv_spinbox_create(root);
    ui.frequency.cont = freq_spinbox;
    ui.frequency.value = 0;
    ui.frequency.state = false;
    lv_obj_remove_style_all(freq_spinbox);
    lv_textarea_set_one_line(freq_spinbox, true);
    lv_textarea_set_cursor_click_pos(freq_spinbox, true);
    lv_obj_set_width(freq_spinbox, 120);
    lv_obj_set_height(freq_spinbox, 82);
    lv_obj_set_x(freq_spinbox, -55);
    lv_obj_set_y(freq_spinbox, -16);
    lv_obj_set_align(freq_spinbox, LV_ALIGN_CENTER);
    lv_spinbox_set_digit_format(freq_spinbox, 5, 0);
    lv_spinbox_set_range(freq_spinbox, 0, 99999);
    lv_spinbox_set_step(freq_spinbox, 1);
    lv_spinbox_set_value(freq_spinbox, 5000);
    lv_obj_set_style_bg_color(freq_spinbox, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(freq_spinbox, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(freq_spinbox, LV_FONT_MONTSERRAT_30, LV_PART_INDICATOR);
    lv_obj_set_style_text_color(freq_spinbox, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(freq_spinbox, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(freq_spinbox, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(freq_spinbox, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(freq_spinbox, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(freq_spinbox, 150, LV_PART_CURSOR | LV_STATE_FOCUSED);
    // lv_obj_set_style_bg_opa(freq_spinbox, 150, LV_PART_CURSOR | LV_STATE_DEFAULT);

    lv_obj_t *duty_spinbox = lv_spinbox_create(root);
    ui.duty.cont = duty_spinbox;
    ui.duty.value = 0;
    ui.duty.state = false;
    lv_obj_remove_style_all(duty_spinbox);
    lv_obj_set_width(duty_spinbox, 100);
    lv_obj_set_height(duty_spinbox, 82);
    lv_obj_set_x(duty_spinbox, -65);
    lv_obj_set_y(duty_spinbox, 50 +16);
    lv_obj_set_align(duty_spinbox, LV_ALIGN_CENTER);
    lv_spinbox_set_digit_format(duty_spinbox, 2, 0);
    lv_spinbox_set_range(duty_spinbox, 0, 99);
    lv_spinbox_set_step(duty_spinbox, 1);
    lv_spinbox_set_value(duty_spinbox, 50);
    lv_obj_set_style_bg_color(duty_spinbox, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(duty_spinbox, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(duty_spinbox, LV_FONT_MONTSERRAT_30, LV_PART_INDICATOR);
    lv_obj_set_style_text_color(duty_spinbox, lv_color_hex(0x8E2DA1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(duty_spinbox, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(duty_spinbox, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(duty_spinbox, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(duty_spinbox, lv_color_hex(0xFFFFFF), LV_PART_CURSOR | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(duty_spinbox, 150, LV_PART_CURSOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(duty_spinbox, 150, LV_PART_CURSOR | LV_STATE_FOCUSED);

    lv_obj_t *ui_Label5 = lv_label_create(root);
    ui.unit.cont = ui_Label5;
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, -40);
    lv_obj_set_y(ui_Label5, -12);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "Hz");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0x2C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label7 = lv_label_create(root);
    lv_obj_set_width(ui_Label7, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label7, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label7, -36);
    lv_obj_set_y(ui_Label7, 25 +16);
    lv_obj_set_align(ui_Label7, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label7, "%");
    lv_obj_set_style_text_color(ui_Label7, lv_color_hex(0x8E2DA1), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label7, ResourcePool::GetFont("sf_compact_32"), LV_PART_MAIN | LV_STATE_DEFAULT);

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
}




void HertzView::Delete()
{
    printf("HertzView::Delete()\n");
}

