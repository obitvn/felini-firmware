#include "AppLumiaView.h"
#include <cstdio>

using namespace Page;


void AppLumiaView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    lv_obj_set_style_bg_color(root, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(root, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    // tile view

    lv_obj_t *ui_tileView = lv_tileview_create(root);

    lv_obj_set_width(ui_tileView, 320);
    lv_obj_set_height(ui_tileView, 440);

    lv_obj_set_x(ui_tileView, 0);
    lv_obj_set_y(ui_tileView, -20);

    lv_obj_set_align(ui_tileView, LV_ALIGN_CENTER);

    lv_obj_set_scrollbar_mode(ui_tileView, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_radius(ui_tileView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_tileView, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tileView, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_tileView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Tile1: startMenu*/
    lv_obj_t *ui_tileStart = lv_tileview_add_tile(ui_tileView, 0, 0, LV_DIR_RIGHT);

    static lv_coord_t col_dsc[] = {92, 92, 92, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {70, 70, 70, 70, 70, 70, 70, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t *cont = lv_obj_create(ui_tileStart);
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, 320, 440);
    lv_obj_center(cont);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    lv_obj_set_style_pad_top(cont, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    create_tile(cont, "Phone", ResourcePool::GetImage("key"), 0, 0, 1, NULL);
    create_tile(cont, "People", ResourcePool::GetImage("key"), 1, 0, 2, NULL);

    create_tile(cont, "Messaging", ResourcePool::GetImage("key"), 0, 1, 1, NULL);
    create_tile(cont, "Store", ResourcePool::GetImage("key"), 1, 1, 1, NULL);
    create_tile(cont, "Calendar", ResourcePool::GetImage("key"), 2, 1, 1, NULL);

    create_tile(cont, "Files", ResourcePool::GetImage("key"), 0, 2, 1, NULL);
    create_tile(cont, "Weather", ResourcePool::GetImage("key"), 1, 2, 2, NULL);

    create_tile(cont, "Photos", ResourcePool::GetImage("key"), 0, 3, 2, NULL);
    create_tile(cont, "Music", ResourcePool::GetImage("key"), 2, 3, 1, NULL);

    create_tile(cont, "Settings", ResourcePool::GetImage("key"), 0, 4, 1, NULL);
    create_tile(cont, "Maps", ResourcePool::GetImage("key"), 1, 4, 2, NULL);

    create_tile(cont, "OneDrive", ResourcePool::GetImage("key"), 0, 5, 1, NULL);
    create_tile(cont, "Wallet", ResourcePool::GetImage("key"), 1, 5, 1, NULL);
    create_tile(cont, "WiFi", ResourcePool::GetImage("key"), 2, 5, 1, NULL);

    create_tile(cont, "Lock Screen", ResourcePool::GetImage("key"), 0, 6, 1, NULL);
    create_tile(cont, "Sleep", ResourcePool::GetImage("key"), 1, 6, 1, NULL);
    create_tile(cont, "Power Off", ResourcePool::GetImage("key"), 2, 6, 1, NULL);

    /*Tile2: appList*/
    lv_obj_t *ui_tileApps = lv_tileview_add_tile(ui_tileView, 1, 0, LV_DIR_LEFT);
    /*Create a list*/
    lv_obj_t *list1 = lv_list_create(ui_tileApps);
    lv_obj_set_size(list1, 320, 440);
    lv_obj_center(list1);

    lv_obj_set_style_pad_top(list1, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(list1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(list1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(list1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(list1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(list1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_top(list1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(list1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Add apps to the list*/

    add_item(list1, "About", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Arduino Blog", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Calendar", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Edge", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Files", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Mail", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Maps", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Messaging", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Music", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "OneDrive", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "People", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Phone", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Photos", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Power Off", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Settings", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Sleep", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Store", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Test App", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Wallet", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "Weather", ResourcePool::GetImage("key"), NULL);
    add_item(list1, "WiFi", ResourcePool::GetImage("key"), NULL);
}

void AppLumiaView::add_item(lv_obj_t *parent, char *name, const void *src, lv_event_cb_t callback)
{

    lv_obj_t *obj;
    lv_obj_t *icon;
    lv_obj_t *label;

    obj = lv_btn_create(parent);

    lv_obj_set_width(obj, lv_pct(100));
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 10, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_border_width(obj, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    //lv_obj_add_event_cb(obj, callback, LV_EVENT_ALL, name);

    label = lv_label_create(obj);
    lv_label_set_text(label, name);
    lv_obj_center(label);
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(label, 50);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    icon = lv_img_create(obj);
    lv_img_set_src(icon, src);
    lv_obj_set_width(icon, LV_SIZE_CONTENT);
    lv_obj_set_height(icon, LV_SIZE_CONTENT);
    lv_obj_set_x(icon, 5);
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(icon, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(icon, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(icon, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
}

void AppLumiaView::create_tile(lv_obj_t *parent, char *name, const void *src, int col, int row, int size, lv_event_cb_t callback)
{
    lv_obj_t *label;
    lv_obj_t *obj;
    lv_obj_t *icon;
    obj = lv_btn_create(parent);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, size, LV_GRID_ALIGN_STRETCH, row, 1);
    //lv_obj_add_event_cb(obj, callback, LV_EVENT_ALL, name);
    label = lv_label_create(obj);
    lv_label_set_text(label, name);
    lv_obj_center(label);
    lv_obj_set_align(label, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_x(label, -5);
    lv_obj_set_y(label, 5);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);
    icon = lv_img_create(obj);
    lv_img_set_src(icon, src);
    lv_obj_set_width(icon, LV_SIZE_CONTENT);
    lv_obj_set_height(icon, LV_SIZE_CONTENT);
    lv_obj_set_align(icon, LV_ALIGN_CENTER);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);
}

void AppLumiaView::Delete()
{
    printf("AppLumiaView::Delete()");
}

