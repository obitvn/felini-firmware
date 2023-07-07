#include "MenuListView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

lv_obj_t *MenuListView::Btn_Create(lv_obj_t *par, const void *img_src, lv_coord_t x_ofs, lv_coord_t y_ofs)
{
    lv_obj_t *obj = lv_btn_create(par);

    lv_obj_remove_style_all(obj);
    lv_obj_set_width(obj, 64);
    lv_obj_set_height(obj, 64);
    lv_obj_set_x(obj, x_ofs);
    lv_obj_set_y(obj, y_ofs);
    lv_obj_set_align(obj, LV_ALIGN_TOP_LEFT);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);                  /// Flags
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);               /// Flags
    lv_obj_set_style_bg_img_src(obj, img_src, LV_STATE_DEFAULT);

    return obj;
}

void MenuListView::Create(lv_obj_t *root)
{

    static lv_style_t style, style_hide;
    lv_style_init(&style);
    lv_style_init(&style_hide);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, 16);
    lv_style_set_bg_opa(&style, LV_OPA_20);
    lv_style_set_bg_color(&style, lv_color_hex(0x00ff00));

    /*Add border to the bottom+right*/
    lv_style_set_border_color(&style, lv_color_hex(0xFEFEFE));
    lv_style_set_border_width(&style, 1);
    lv_style_set_border_opa(&style, LV_OPA_100);
    lv_style_set_border_side(&style, LV_BORDER_SIDE_FULL);

    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *control_panel = lv_obj_create(root);
    lv_obj_remove_style_all(control_panel);
    lv_obj_set_align(control_panel, LV_ALIGN_CENTER);
    lv_obj_add_style(control_panel, &style, 0);
    lv_obj_set_pos(control_panel, 280/2-72/2-5, 0);
    lv_obj_set_width(control_panel, 72);
    lv_obj_set_height(control_panel, 72*3);
    lv_obj_add_flag(control_panel, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(control_panel, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    ui.controlpanel = control_panel;

    // lv_obj_t *back_button = lv_btn_create(control_panel);
    // lv_obj_remove_style_all(back_button);
    // lv_obj_set_width(back_button, 32);
    // lv_obj_set_height(back_button, 32);
    // lv_obj_set_x(back_button, 10);
    // lv_obj_set_y(back_button, 10);
    // lv_obj_set_align(back_button, LV_ALIGN_TOP_LEFT);
    // lv_obj_add_flag(back_button, LV_OBJ_FLAG_SCROLL_ON_FOCUS); /// Flags
    // lv_obj_clear_flag(back_button, LV_OBJ_FLAG_SCROLLABLE);    /// Flags
    // lv_obj_set_style_bg_img_src(back_button, ResourcePool::GetImage("back_blue_png"), LV_STATE_DEFAULT);

    // ui.back = Btn_Create(control_panel, ResourcePool::GetImage("back_blue_png"), 10, 10);
    // ui.list_menu = Btn_Create(control_panel, ResourcePool::GetImage("list_menu_blue_png"), 74, 10);
    // ui.home = Btn_Create(control_panel, ResourcePool::GetImage("home_blue_png"), 74+64, 10);
    // ui.settings = Btn_Create(control_panel, ResourcePool::GetImage("settings_blue_png"), 136, 10);
    // ui.remove = Btn_Create(control_panel, ResourcePool::GetImage("remove_blue_png"), 74+64*2, 10);

    ui.back = Btn_Create(control_panel, ResourcePool::GetImage("back_blue_png"), 10, 10);
    ui.home = Btn_Create(control_panel, ResourcePool::GetImage("back_blue_png"), 10, 72+10);
    ui.setting = Btn_Create(control_panel, ResourcePool::GetImage("back_blue_png"), 10, 72*2+10);
    

    lv_obj_add_flag(ui.controlpanel, LV_OBJ_FLAG_HIDDEN);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style_hide, 16);
    lv_style_set_bg_opa(&style_hide, LV_OPA_80);
    lv_style_set_bg_color(&style_hide, lv_color_hex(0xFEFEFE));

    /*Add border to the bottom+right*/
    lv_style_set_border_color(&style_hide, lv_color_hex(0xFEFEFE));
    lv_style_set_border_width(&style_hide, 1);
    lv_style_set_border_opa(&style_hide, LV_OPA_80);
    lv_style_set_border_side(&style_hide, LV_BORDER_SIDE_FULL);

    lv_obj_t *obj_control = lv_obj_create(root);
    lv_obj_remove_style_all(obj_control);
    // lv_obj_set_align(obj_control, LV_ALIGN_CENTER);
    lv_obj_add_style(obj_control, &style_hide, 0);
    lv_obj_set_width(obj_control, 16);
    lv_obj_set_height(obj_control, 160);
    lv_obj_set_x(obj_control, 270);//stop at 240- 124
    lv_obj_set_y(obj_control, 40); 
    ui.control = obj_control;
}

void MenuListView::ShowControlPanel()
{
    lv_obj_clear_flag(ui.controlpanel, LV_OBJ_FLAG_HIDDEN);
}

void MenuListView::SetDefaultControlPanel()
{
    lv_obj_add_flag(ui.controlpanel, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_pos(ui.control, 45, 217);
    lv_obj_clear_flag(ui.control, LV_OBJ_FLAG_HIDDEN);
}

void MenuListView::Delete()
{
}