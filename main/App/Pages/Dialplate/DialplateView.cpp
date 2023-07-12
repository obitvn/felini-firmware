#include "DialplateView.h"
#include <cstdio>

using namespace Page;


void DialplateView::Create(lv_obj_t *root)
{

    static lv_style_t style, style_hide;
    lv_style_init(&style);
    lv_style_init(&style_hide);

    /*Set a background color and a radius*/
    lv_style_set_radius(&style, 16);
    lv_style_set_bg_opa(&style, LV_OPA_100);
    lv_style_set_bg_color(&style, lv_color_hex(0));

    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *cont = lv_obj_create(root);
    scroll_panel.cont = cont;
    lv_obj_remove_style_all(cont);
    lv_obj_add_style(cont, &style, 0);
    lv_obj_set_size(cont, 240, 240);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_ON);

    Item_Create(&ui.uart, cont, "usb uart1", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    Item_Create(&ui.iic, cont, "usb uart2", ResourcePool::GetImage("home_blue_png"), "Pages/PowerSupply");
    Item_Create(&ui.setting, cont, "usb uart0", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    Item_Create(&ui.spi, cont, "usb uart     3", ResourcePool::GetImage("home_blue_png"), "Pages/PowerSupply");
    Item_Create(&ui.a, cont, "usb uart4", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    Item_Create(&ui.b, cont, "usb uart5", ResourcePool::GetImage("home_blue_png"), "Pages/PowerSupply");
    Item_Create(&ui.c, cont, "usb uart6", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.d, cont, "usb uart7", ResourcePool::GetImage("home_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.e, cont, "usb uart8", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.f, cont, "usb uart9", ResourcePool::GetImage("home_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.g, cont, "usb uart10", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.h, cont, "usb uart11", ResourcePool::GetImage("home_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.i, cont, "usb uart12", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");
    // Item_Create(&ui.k, cont, "usb uart13", ResourcePool::GetImage("remove_blue_png"), "Pages/PowerSupply");

    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 3), LV_ANIM_OFF);
    /*Update the buttons position manually for first*/
    UpdatePosItem(cont);
}



void DialplateView::UpdatePosItem(lv_obj_t *cont)
{
    lv_area_t cont_a;

    static lv_style_t style;
    lv_style_init(&style);

    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2 + 3;

    lv_coord_t r = lv_obj_get_height(cont) * 6.2 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for (i = 0; i < child_cnt; i++)
    {
        lv_obj_t *child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if (diff_y >= r)
        {
            x = r;
        }
        else
        {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000); /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        if(x <320) lv_obj_set_style_translate_x(child, x, 0);
        else x = 0;

        // /*Use some opacity with larger translations*/
        // lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        // lv_obj_set_style_opa(child, 100, 0);
    }
}


// void DialplateView::Item_Create(item_t *item, lv_obj_t *par, const char *name, const void *img_src, const char *app_src)
// {
//     static lv_style_t style, style_hide;
//     lv_style_init(&style);
//     lv_style_init(&style_hide);

//     /*Set a background color and a radius*/
//     lv_style_set_radius(&style, 16);
//     lv_style_set_bg_opa(&style, LV_OPA_100);
//     lv_style_set_bg_color(&style, lv_color_hex(0));

//     /*Add border to the bottom+right*/
//     lv_style_set_border_color(&style, lv_color_hex(0));
//     lv_style_set_border_width(&style, 1);
//     lv_style_set_border_opa(&style, LV_OPA_100);
//     lv_style_set_border_side(&style, LV_BORDER_SIDE_FULL);

//     // creat panel for item
//     lv_obj_t *cont = lv_obj_create(par);
//     item->cont = cont;
//     item->app_src = app_src;
//     lv_obj_enable_style_refresh(false);
//     lv_obj_remove_style_all(cont);
//     lv_obj_set_width(cont, 180);
//     lv_obj_set_height(cont, 80);
//     // lv_obj_set_x(cont, lv_pct(0));
//     // lv_obj_set_y(cont, lv_pct(0)); 
//     lv_obj_add_style(cont, &style, 0);
//     lv_obj_set_align(cont, LV_ALIGN_CENTER);
//     lv_obj_add_flag(cont, LV_OBJ_FLAG_CLICKABLE);
//     // creat panel for icon
//     lv_obj_t *img_cont = lv_img_create(cont);
//     lv_obj_remove_style_all(img_cont);
//     lv_obj_set_width(img_cont, LV_SIZE_CONTENT);
//     lv_obj_set_height(img_cont, LV_SIZE_CONTENT);
//     lv_obj_set_align(img_cont, LV_ALIGN_LEFT_MID);
//     lv_img_set_src(img_cont, img_src);
//     lv_obj_set_x(img_cont, 5);
//     lv_obj_set_y(img_cont, 0);
//     item->icon = img_cont;

//     // creat panel for text
//     lv_obj_t *label = lv_label_create(cont);
//     lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), 0);
//     lv_obj_set_style_text_font(label, ResourcePool::GetFont("SFCompact22bpp8"), 0);
//     lv_obj_set_width(label, LV_SIZE_CONTENT);  
//     lv_obj_set_height(label, LV_SIZE_CONTENT); 
//     lv_obj_set_x(label, 32);
//     lv_obj_set_y(label, 0);
//     lv_obj_set_x(label, 32 + 32);
//     lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
//     lv_label_set_text(label, name);
//     item->labelInfo = label;
// }

#define ITEM_HEIGHT_MIN 100
#define OV_MAX(a, b) ((a) > (b) ? (a) : (b))

void DialplateView::Item_Create(item_t *item, lv_obj_t *par, const char *name, const void *img_src, const char *app_src)
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(cont);
    lv_obj_set_width(cont, 220);

    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    item->cont = cont;

    /* icon */
    lv_obj_t *icon = lv_obj_create(cont);
    lv_obj_enable_style_refresh(false);
    lv_obj_remove_style_all(icon);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);

    lv_obj_add_style(icon, &style.icon, 0);
    lv_obj_add_style(icon, &style.focus, LV_STATE_FOCUSED);
    lv_obj_set_style_align(icon, LV_ALIGN_LEFT_MID, 0);

    lv_obj_set_flex_flow(icon, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(
        icon,
        LV_FLEX_ALIGN_SPACE_AROUND,
        LV_FLEX_ALIGN_CENTER,
        LV_FLEX_ALIGN_CENTER);

    lv_obj_t *img = lv_img_create(icon);
    lv_obj_enable_style_refresh(false);
    lv_img_set_src(img, img_src);

    lv_obj_t *label = lv_label_create(icon);
    lv_obj_enable_style_refresh(false);
    lv_label_set_text(label, name);
    item->icon = icon;

    lv_obj_move_foreground(icon);
    lv_obj_enable_style_refresh(true);

    /* get real max height */
    lv_obj_update_layout(item->labelInfo);
    lv_coord_t height = lv_obj_get_height(item->labelInfo);
    height = OV_MAX(height, ITEM_HEIGHT_MIN);
    lv_obj_set_height(cont, height);
    lv_obj_set_height(icon, height);
}

void DialplateView::Delete()
{

}

