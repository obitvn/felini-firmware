

#include "ServoCtrlView.h"
#include <cstdio>

using namespace Page;


void ServoCtrlView::Create(lv_obj_t *root)
{
    /*Change the active screen's background color*/
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_ArcServo = lv_arc_create(root);
    lv_arc_set_angles(ui_ArcServo, 0, 180);
    lv_arc_set_rotation(ui_ArcServo, 0);
    lv_arc_set_range(ui_ArcServo, 0 , 180);
    lv_obj_set_flex_flow(ui_ArcServo, LV_FLEX_FLOW_ROW);
    lv_obj_set_width(ui_ArcServo, 170);
    lv_obj_set_height(ui_ArcServo, 170);
    lv_obj_set_x(ui_ArcServo, -4);
    lv_obj_set_y(ui_ArcServo, -10);
    lv_obj_set_align(ui_ArcServo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_ArcServo, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
    // lv_obj_set_scrollbar_mode(ui_ArcServo, LV_SCROLLBAR_MODE_OFF);

    ui.arc.cont = ui_ArcServo;

    lv_group_t *arc_group = lv_group_get_default();
    lv_indev_set_group(lv_get_indev(LV_INDEV_TYPE_ENCODER), arc_group);
    lv_group_add_obj(arc_group, ui.arc.cont);
    lv_group_focus_obj(ui.arc.cont);

    lv_obj_t *spinbox = lv_spinbox_create(root);
    lv_obj_remove_style_all(spinbox);
    lv_obj_set_x(spinbox, 320);
    lv_obj_set_y(spinbox, 320);
    lv_spinbox_set_cursor_pos(spinbox, 0);
    lv_spinbox_set_digit_format(spinbox, 1, 1);
    lv_spinbox_set_range(spinbox, 0, 180);
    lv_spinbox_set_step(spinbox, 1);
    ui.spin.cont = spinbox;

    lv_obj_t *ui_ServoAngle = lv_label_create(root);
    lv_obj_set_width(ui_ServoAngle, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_ServoAngle, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_ServoAngle, -8);
    lv_obj_set_y(ui_ServoAngle, -29);
    lv_obj_set_align(ui_ServoAngle, LV_ALIGN_CENTER);
    // lv_label_set_text(ui_ServoAngle, "160");
    uint16_t valu = 0;
    lv_label_set_text_fmt(ui_ServoAngle, "%d", valu);
    lv_obj_set_style_text_color(ui_ServoAngle, lv_color_hex(0x079DF9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ServoAngle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_ServoAngle, ResourcePool::GetFont("sf_compact_48"), LV_PART_MAIN | LV_STATE_DEFAULT);
    ui.angle.cont = ui_ServoAngle;

    lv_obj_t *ui_TitleApp = lv_label_create(root);
    lv_obj_set_width(ui_TitleApp, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_TitleApp, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_TitleApp, -6);
    lv_obj_set_y(ui_TitleApp, 18);
    lv_obj_set_align(ui_TitleApp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TitleApp, "Servo\ncontroler");
    lv_obj_set_style_text_color(ui_TitleApp, lv_color_hex(0xEAF3F4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TitleApp, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_TitleApp, ResourcePool::GetFont("sf_compact_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_PinMap = lv_label_create(root);
    lv_obj_set_width(ui_PinMap, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_PinMap, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_PinMap, -100);
    lv_obj_set_y(ui_PinMap, 88);
    lv_obj_set_align(ui_PinMap, LV_ALIGN_CENTER);
    lv_label_set_text(ui_PinMap, "ROW1");
    lv_obj_set_style_text_color(ui_PinMap, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_PinMap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Title = lv_label_create(root);
    lv_obj_set_width(ui_Title, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Title, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Title, -85);
    lv_obj_set_y(ui_Title, 108);
    lv_obj_set_align(ui_Title, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Title, "Servo pins");
    lv_obj_set_style_text_color(ui_Title, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Title, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_PinMapIMG = lv_img_create(root);
    lv_img_set_src(ui_PinMapIMG, ResourcePool::GetImage("pin_servoch"));
    lv_img_set_zoom(ui_PinMapIMG, 280);
    lv_obj_set_width(ui_PinMapIMG, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_PinMapIMG, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_PinMapIMG, 95);
    lv_obj_set_y(ui_PinMapIMG, 95);
    lv_obj_set_align(ui_PinMapIMG, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PinMapIMG, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_PinMapIMG, LV_OBJ_FLAG_SCROLLABLE); /// Flags
}




void ServoCtrlView::Delete()
{
    printf("ServoCtrlView::Delete()\n");
}

