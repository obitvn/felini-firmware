#include "UARTViewerView.h"
#include <cstdio>

using namespace Page;


void UARTViewerView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_t *ui_Label4 = lv_label_create(root);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label4, -105);
    lv_obj_set_y(ui_Label4, 98);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "UART");
    lv_obj_set_style_text_color(ui_Label4, lv_color_hex(0x0090FE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label4, ResourcePool::GetFont("sf_compact_22"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Label5 = lv_label_create(root);
    ui.baud.cont = ui_Label5;
    lv_obj_set_width(ui_Label5, LV_SIZE_CONTENT);  /// 1
    lv_obj_set_height(ui_Label5, LV_SIZE_CONTENT); /// 1
    lv_obj_set_x(ui_Label5, -11);
    lv_obj_set_y(ui_Label5, 98);
    lv_obj_set_align(ui_Label5, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label5, "115200 8N1");
    lv_obj_set_style_text_color(ui_Label5, lv_color_hex(0xCF1031), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Label5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_Label5, ResourcePool::GetFont("sf_compact_20"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t *ui_Image4 = lv_img_create(root);
    lv_img_set_src(ui_Image4, ResourcePool::GetImage("pin_uart"));
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);  /// 79
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT); /// 16
    lv_obj_set_x(ui_Image4, 100);
    lv_obj_set_y(ui_Image4, 98);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE); /// Flags

    lv_obj_t *ui_TextArea1 = lv_textarea_create(root);
    ui.text.cont = ui_TextArea1;
    lv_textarea_set_max_length(ui_TextArea1, 2048);
    lv_obj_remove_style_all(ui_TextArea1);
    lv_obj_set_width(ui_TextArea1, 280);
    lv_obj_set_height(ui_TextArea1, 200);
    lv_obj_set_x(ui_TextArea1, 0);
    lv_obj_set_y(ui_TextArea1, -20);
    lv_obj_set_align(ui_TextArea1, LV_ALIGN_CENTER);
    lv_obj_set_style_radius(ui_TextArea1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_textarea_set_placeholder_text(ui_TextArea1, "");
    lv_obj_set_style_text_color(ui_TextArea1, lv_color_hex(0x39D82B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TextArea1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TextArea1, lv_color_hex(0x1c1c1c), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TextArea1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_TextArea1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_TextArea1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_TextArea1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_TextArea1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_TextArea1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_clear_flag(ui_TextArea1, LV_OBJ_FLAG_CLICK_FOCUSABLE); /// Flags
    lv_obj_set_style_border_width(ui_TextArea1, 0, LV_PART_SELECTED | LV_STATE_DEFAULT);

    lv_obj_t *ui_Keyboard1 = lv_keyboard_create(root);
    ui.keyboard.cont = ui_Keyboard1;
    lv_obj_set_width(ui_Keyboard1, 280);
    lv_obj_set_height(ui_Keyboard1, 120);
    lv_obj_set_align(ui_Keyboard1, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Keyboard1, LV_OBJ_FLAG_HIDDEN);
}




void UARTViewerView::Delete()
{
    printf("UARTViewerView::Delete()\n");
}

