#include "DAPLinkView.h"
#include <cstdio>

using namespace Page;


void DAPLinkView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Label1 = lv_label_create(root);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label1, -3);
    lv_obj_set_y(ui_Label1, -85);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "DAPLink");
    lv_obj_set_style_text_color(ui_Label1, lv_color_hex(0xFF6610), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label1, ResourcePool::GetFont("sf_compact_42"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label2 = lv_label_create(root);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label2, -5);
    lv_obj_set_y(ui_Label2, -31);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "Connect to USB");
    lv_obj_set_style_text_color(ui_Label2, lv_color_hex(0x08A3FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label2, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Image1 = lv_img_create(root);
    lv_img_set_src(ui_Image1, ResourcePool::GetImage("dap_connected"));
    lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);  /// 36
    lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT); /// 36
    lv_obj_set_x(ui_Image1, -104);
    lv_obj_set_y(ui_Image1, -33);
    lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ui_Image2 = lv_img_create(root);
    lv_img_set_src(ui_Image2, ResourcePool::GetImage("down_dap"));
    lv_obj_set_width(ui_Image2, LV_SIZE_CONTENT);  /// 48
    lv_obj_set_height(ui_Image2, LV_SIZE_CONTENT); /// 48
    lv_obj_set_x(ui_Image2, 105);
    lv_obj_set_y(ui_Image2, -33);
    lv_obj_set_align(ui_Image2, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image2, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image2, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ui_Image3 = lv_img_create(root);
    lv_img_set_src(ui_Image3, ResourcePool::GetImage("dap_bug"));
    lv_obj_set_width(ui_Image3, LV_SIZE_CONTENT);  /// 48
    lv_obj_set_height(ui_Image3, LV_SIZE_CONTENT); /// 48
    lv_obj_set_x(ui_Image3, 105);
    lv_obj_set_y(ui_Image3, 10);
    lv_obj_set_align(ui_Image3, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image3, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image3, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    // lv_obj_t *ui_Switch1 = lv_switch_create(root);
    // lv_obj_set_width(ui_Switch1, 50);
    // lv_obj_set_height(ui_Switch1, 25);
    // lv_obj_set_x(ui_Switch1, -103);
    // lv_obj_set_y(ui_Switch1, 17);
    // lv_obj_set_align(ui_Switch1, LV_ALIGN_CENTER);
    // switch_cont = ui_Switch1;

    // lv_obj_t *ui_Label3 = lv_label_create(root);
    // lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT); /// 1
    // lv_obj_set_x(ui_Label3, -42);
    // lv_obj_set_y(ui_Label3, 17);
    // lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    // lv_label_set_text(ui_Label3, "SWD");
    // lv_obj_set_style_text_color(ui_Label3, lv_color_hex(0x08A3FB), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(ui_Label3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui_Label3, ResourcePool::GetFont("sf_compact_18"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *pindaplinkObj = lv_img_create(root);
    lv_img_set_src(pindaplinkObj, ResourcePool::GetImage("pin_daplink"));
    lv_obj_set_width(pindaplinkObj, LV_SIZE_CONTENT);  /// 209
    lv_obj_set_height(pindaplinkObj, LV_SIZE_CONTENT); /// 70
    lv_obj_set_x(pindaplinkObj, 0);
    lv_obj_set_y(pindaplinkObj, 83);
    lv_obj_set_align(pindaplinkObj, LV_ALIGN_CENTER);
    lv_obj_add_flag(pindaplinkObj, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(pindaplinkObj, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_img_set_zoom(pindaplinkObj, 280);

    lv_obj_t *ui_Label4 = lv_label_create(root);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label4, -20);
    lv_obj_set_y(ui_Label4, 40);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "connection pins is row 2");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0xFB0808), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, ResourcePool::GetFont("sf_compact_16"), LV_PART_MAIN | LV_STATE_DEFAULT);
}




void DAPLinkView::Delete()
{
    printf("DAPLinkView::Delete()\n");
}

