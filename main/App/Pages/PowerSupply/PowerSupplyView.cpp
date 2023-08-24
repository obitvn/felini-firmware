#include "PowerSupplyView.h"
#include <cstdio>

using namespace Page;


void PowerSupplyView::Create(lv_obj_t *root)
{
    /*Change the active screen's background color*/
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_VoltageButton = lv_btn_create(root);
    ui.voltage.button = ui_VoltageButton;
    lv_obj_set_width(ui_VoltageButton, 237);
    lv_obj_set_height(ui_VoltageButton, 60);
    lv_obj_set_x(ui_VoltageButton, 21 - 20);
    lv_obj_set_y(ui_VoltageButton, 17 - 20);
    lv_obj_add_flag(ui_VoltageButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_VoltageButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_VoltageButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_VoltageButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_VoltageButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_VoltageButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_VoltageButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_VoltageButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_VoltageButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_VoltageButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_VoltageButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbvolt = lv_label_create(root);
    lv_obj_set_width(ui_lbvolt, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbvolt, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbvolt, 28 - 20);
    lv_obj_set_y(ui_lbvolt, 20 - 20);
    lv_label_set_text(ui_lbvolt, "VOLTAGE");
    lv_obj_set_style_text_color(ui_lbvolt, lv_color_hex(0x538DDF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbvolt, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbvolt, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_LbVoltRead = lv_label_create(root);
    lv_obj_set_width(ui_LbVoltRead, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LbVoltRead, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LbVoltRead, 28 - 20);
    lv_obj_set_y(ui_LbVoltRead, 42 - 20);
    lv_label_set_text(ui_LbVoltRead, "12.48 V");
    lv_obj_set_style_text_color(ui_LbVoltRead, lv_color_hex(0x4284E4), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbVoltRead, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbVoltRead, ResourcePool::GetFont("sf_compact_medium_36"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel1 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel1, 222);
    lv_obj_set_height(ui_Panel1, 2);
    lv_obj_set_x(ui_Panel1, 29 - 20);
    lv_obj_set_y(ui_Panel1, 41 - 20);
    lv_obj_clear_flag(ui_Panel1, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel1, lv_color_hex(0x8569FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbtypec = lv_label_create(root);
    lv_obj_set_width(ui_lbtypec, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbtypec, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbtypec, 121 - 20);
    lv_obj_set_y(ui_lbtypec, 20 - 20);
    lv_label_set_text(ui_lbtypec, "[PD- PPS]");
    lv_obj_set_style_text_color(ui_lbtypec, lv_color_hex(0x79B84F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbtypec, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbtypec, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbvset = lv_label_create(root);
    lv_obj_set_width(ui_lbvset, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbvset, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbvset, 220 - 20);
    lv_obj_set_y(ui_lbvset, 21 - 20);
    lv_label_set_text(ui_lbvset, "SET");
    lv_obj_set_style_text_color(ui_lbvset, lv_color_hex(0xD368E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbvset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbvset, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_CurrentButton = lv_btn_create(root);
    ui.current.button = ui_CurrentButton;
    lv_obj_set_width(ui_CurrentButton, 237);
    lv_obj_set_height(ui_CurrentButton, 60);
    lv_obj_set_x(ui_CurrentButton, 20 - 20);
    lv_obj_set_y(ui_CurrentButton, 87 - 20);
    lv_obj_add_flag(ui_CurrentButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_CurrentButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_CurrentButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CurrentButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CurrentButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CurrentButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_CurrentButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_CurrentButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_CurrentButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_CurrentButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_CurrentButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel2 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel2, 222);
    lv_obj_set_height(ui_Panel2, 2);
    lv_obj_set_x(ui_Panel2, 28 - 20);
    lv_obj_set_y(ui_Panel2, 111 - 20);
    lv_obj_clear_flag(ui_Panel2, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0x8569FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbcurrent = lv_label_create(root);
    lv_obj_set_width(ui_lbcurrent, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbcurrent, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbcurrent, 29 - 20);
    lv_obj_set_y(ui_lbcurrent, 90 - 20);
    lv_label_set_text(ui_lbcurrent, "CURRENT");
    lv_obj_set_style_text_color(ui_lbcurrent, lv_color_hex(0x538DDF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbcurrent, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbcurrent, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbcset = lv_label_create(root);
    lv_obj_set_width(ui_lbcset, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbcset, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbcset, 220 - 20);
    lv_obj_set_y(ui_lbcset, 90 - 20);
    lv_label_set_text(ui_lbcset, "SET");
    lv_obj_set_style_text_color(ui_lbcset, lv_color_hex(0xD368E3), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbcset, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbcset, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_LbCurrentRead = lv_label_create(root);
    lv_obj_set_width(ui_LbCurrentRead, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LbCurrentRead, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LbCurrentRead, 28 - 20);
    lv_obj_set_y(ui_LbCurrentRead, 111 - 20);
    lv_label_set_text(ui_LbCurrentRead, "3.62 A");
    lv_obj_set_style_text_color(ui_LbCurrentRead, lv_color_hex(0x40AD33), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbCurrentRead, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbCurrentRead, ResourcePool::GetFont("sf_compact_medium_36"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_PowerButton = lv_btn_create(root);
    ui.power.button = ui_PowerButton;
    lv_obj_set_width(ui_PowerButton, 138);
    lv_obj_set_height(ui_PowerButton, 60);
    lv_obj_set_x(ui_PowerButton, 21 - 20);
    lv_obj_set_y(ui_PowerButton, 156 - 20);
    // lv_obj_add_flag(ui_PowerButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_PowerButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_PowerButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_PowerButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_PowerButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_PowerButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_PowerButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_PowerButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_PowerButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_PowerButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_PowerButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbpowerstate = lv_label_create(root);
    ui.confirm.label = ui_lbpowerstate;
    lv_obj_set_width(ui_lbpowerstate, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbpowerstate, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbpowerstate, 170 - 20);
    lv_obj_set_y(ui_lbpowerstate, 157 - 20);
    lv_label_set_text(ui_lbpowerstate, "ACTIVATE");
    lv_obj_set_style_text_color(ui_lbpowerstate, lv_color_hex(0x15CC34), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbpowerstate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbpowerstate, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_lbpower = lv_label_create(root);
    lv_obj_set_width(ui_lbpower, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_lbpower, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_lbpower, 28 - 20);
    lv_obj_set_y(ui_lbpower, 157 - 20);
    lv_label_set_text(ui_lbpower, "POWER");
    lv_obj_set_style_text_color(ui_lbpower, lv_color_hex(0x538DDF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lbpower, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lbpower, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Panel3 = lv_obj_create(root);
    lv_obj_set_width(ui_Panel3, 222);
    lv_obj_set_height(ui_Panel3, 2);
    lv_obj_set_x(ui_Panel3, 28 - 20);
    lv_obj_set_y(ui_Panel3, 176 - 20);
    lv_obj_clear_flag(ui_Panel3, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0x8569FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Panel3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_Panel3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_LbPowerConsume = lv_label_create(root);
    lv_obj_set_width(ui_LbPowerConsume, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LbPowerConsume, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LbPowerConsume, 27 - 20);
    lv_obj_set_y(ui_LbPowerConsume, 178 - 20);
    lv_label_set_text(ui_LbPowerConsume, "65.23 W");
    lv_obj_set_style_text_color(ui_LbPowerConsume, lv_color_hex(0xDA5136), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbPowerConsume, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbPowerConsume, ResourcePool::GetFont("sf_compact_medium_36"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_LbVoltSet = lv_label_create(root);
    ui.voltage.label = ui_LbVoltSet;
    lv_obj_set_width(ui_LbVoltSet, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LbVoltSet, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LbVoltSet, 203 - 20);
    lv_obj_set_y(ui_LbVoltSet, 59 - 20);
    lv_label_set_text(ui_LbVoltSet, "19.82");
    lv_obj_set_style_text_color(ui_LbVoltSet, lv_color_hex(0x13C0BE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbVoltSet, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbVoltSet, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);


    lv_obj_t *ui_LbCurrentSet = lv_label_create(root);
    ui.current.label = ui_LbCurrentSet;
    lv_obj_set_width(ui_LbCurrentSet, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_LbCurrentSet, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_LbCurrentSet, 207 - 20);
    lv_obj_set_y(ui_LbCurrentSet, 127 - 20);
    lv_label_set_text(ui_LbCurrentSet, "2.82");
    lv_obj_set_style_text_color(ui_LbCurrentSet, lv_color_hex(0x13C0BE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LbCurrentSet, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LbCurrentSet, ResourcePool::GetFont("sf_compact_medium_16"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_ConfirmButton = lv_btn_create(root);
    ui.confirm.button = ui_ConfirmButton;
    lv_obj_set_width(ui_ConfirmButton, 102);
    lv_obj_set_height(ui_ConfirmButton, 59);
    lv_obj_set_x(ui_ConfirmButton, 163 - 20);
    lv_obj_set_y(ui_ConfirmButton, 156 - 20);
    lv_obj_add_flag(ui_ConfirmButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    lv_obj_clear_flag(ui_ConfirmButton, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    lv_obj_set_style_bg_color(ui_ConfirmButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ConfirmButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui_ConfirmButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui_ConfirmButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui_ConfirmButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui_ConfirmButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void PowerSupplyView::EditLabel(lv_obj_t *label, float value)
{
    lv_label_set_text_fmt(label, "%.2f", value);
    lv_obj_set_style_border_color(label, lv_color_hex(0x0A84FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(label, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(label, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(label, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void PowerSupplyView::ExitEditLabel(lv_obj_t *label)
{
    lv_obj_set_style_border_opa(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(label, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void PowerSupplyView::Delete()
{
    printf("PowerSupplyView::Delete()");
}

