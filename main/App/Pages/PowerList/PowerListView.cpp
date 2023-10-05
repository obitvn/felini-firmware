#include "PowerListView.h"
#include <cstdio>

using namespace Page;

#define CELL_SIZE 80

void PowerListView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);
    // tile view

    lv_obj_t *ui_tileView = lv_tileview_create(root);

    lv_obj_set_width(ui_tileView, 280);
    lv_obj_set_height(ui_tileView, 240);
    lv_obj_center(ui_tileView);

    lv_obj_set_align(ui_tileView, LV_ALIGN_CENTER);

    lv_obj_set_scrollbar_mode(ui_tileView, LV_SCROLLBAR_MODE_OFF);

    lv_obj_set_style_radius(ui_tileView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_tileView, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_tileView, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_tileView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Tile1: startMenu*/
    lv_obj_t *ui_tileStart = lv_tileview_add_tile(ui_tileView, 0, 0, LV_DIR_RIGHT);

    static lv_coord_t col_dsc[] = {CELL_SIZE, CELL_SIZE, CELL_SIZE, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t *cont = lv_obj_create(ui_tileStart);

    lv_obj_set_style_radius(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(cont, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(cont, ResourcePool::GetImage("wall"), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    // lv_obj_set_style_pad_all(cont, 20, LV_PART_MAIN);
    lv_obj_set_style_pad_left(cont, 12, LV_PART_MAIN);
    lv_obj_set_style_pad_right(cont, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_column(cont, 8, LV_PART_MAIN);
    lv_obj_set_style_pad_row(cont, 8, LV_PART_MAIN);
    lv_obj_set_style_grid_column_dsc_array(cont, col_dsc, 0);
    lv_obj_set_style_grid_row_dsc_array(cont, row_dsc, 0);
    lv_obj_set_size(cont, 280, 240);
    lv_obj_center(cont);
    lv_obj_set_layout(cont, LV_LAYOUT_GRID);

    CreateItemCell(3.3, cont, "3.3", 0x6d6ed8, 0, 0, 2, &ui.analog);
    CreateItemCell(3.7, cont, "LED", 0x6d6ed8, 2, 0, 1, &ui.ledcolor);
    CreateItemCell(4.2, cont, "Interval", 0x43b3db, 0, 1, 1, &ui.timekeeper);
    CreateItemCell(4.8, cont, "I2C", 0x94339c, 1, 1, 1, &ui.i2cscan);
    CreateItemCell(5.0, cont, "Hertz", 0x2c78a0,  2, 1, 1, &ui.frequency);
    CreateItemCell(5.5, cont, "Servo", 0x16b0a0, 0, 2, 1, &ui.ccpmservo);
    CreateItemCell(6.4, cont, "UART", 0x16b0a0, 1, 2, 2, &ui.uartter);
    CreateItemCell(7.4, cont, "DAPLink", 0x43b3db, 0, 3, 2, &ui.daplink);
    CreateItemCell(8.4, cont, "USB LA", 0x2c78a0, 2, 3, 1, &ui.logicanalyzer);
    CreateItemCell(10.6, cont, "CAN Bus", 0x16b0a0, 0, 4, 1, &ui.usbcanbus);
    CreateItemCell(11.1, cont, "PD PPS", 0x16b0a0, 1, 4, 2, &ui.powerpd);
    CreateItemCell(13.2, cont, "KEY", 0x6d6ed8, 0, 5, 1, &ui.kaitokey);
    CreateItemCell(14.2, cont, "IMU", 0x6d6ed8, 1, 5, 1, &ui.imu);
    CreateItemCell(16.8, cont, "Setting", 0x43b3db, 2, 5, 1, &ui.setting);
    CreateItemCell(16.8, cont, "Setting", 0x94339c, 2, 5, 1, &ui.setting);
}

void PowerListView::CreateItemCell(float voltage, lv_obj_t *parent, const char *name, uint32_t color, int col, int row, int size, item_t *item)
{
    lv_obj_t *label;
    lv_obj_t *obj;
    lv_obj_t *icon;
    item->volt = voltage;

    // printf("app src %s\r\n", app_src);
    obj = lv_btn_create(parent);
    item->btn_cell = obj;
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(color), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, size, LV_GRID_ALIGN_STRETCH, row, 1);

    label = lv_label_create(obj);
    item->labelInfo = label;
    lv_label_set_text_fmt(label, "%.1f", voltage);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("sf_compact_medium_24"), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_width(label, LV_SIZE_CONTENT);
    lv_obj_set_height(label, LV_SIZE_CONTENT);
    lv_obj_set_align(label, LV_ALIGN_CENTER);
    lv_obj_add_flag(label, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(label, LV_OBJ_FLAG_SCROLLABLE);
}

void PowerListView::Delete()
{
    printf("PowerListView::Delete()\n");
}

