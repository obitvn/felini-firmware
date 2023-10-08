#include "AppLumiaView.h"
#include <cstdio>

using namespace Page;

#define CELL_SIZE 80

void AppLumiaView::Create(lv_obj_t *root)
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
    // lv_obj_set_style_bg_color(ui_tileView, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_opa(ui_tileView, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_tileView, ResourcePool::GetImage("triangles"), LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_border_width(ui_tileView, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Tile1: startMenu*/
    lv_obj_t *ui_tileStart = lv_tileview_add_tile(ui_tileView, 0, 0, LV_DIR_RIGHT);

    static lv_coord_t col_dsc[] = {CELL_SIZE, CELL_SIZE, CELL_SIZE, LV_GRID_TEMPLATE_LAST};
    static lv_coord_t row_dsc[] = {CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, CELL_SIZE, LV_GRID_TEMPLATE_LAST};

    /*Create a container with grid*/
    lv_obj_t *cont = lv_obj_create(ui_tileStart);

    lv_obj_set_style_radius(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(cont, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(cont, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_img_src(cont, ResourcePool::GetImage("triangles"), LV_PART_MAIN | LV_STATE_DEFAULT);
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

    CreateItemCell("Pages/AnalogViewer", cont, "ADC", "analog", 0, 0, 2, &ui.analog);
    CreateItemCell("Pages/ColorWheel", cont, "LED", "color", 2, 0, 1, &ui.ledcolor);
    CreateItemCell("Pages/Interval", cont, "Interval", "clock", 0, 1, 1, &ui.timekeeper);
    CreateItemCell("Pages/IICDiscovery", cont, "I2C", "i2cnetwork", 1, 1, 1, &ui.i2cscan);
    CreateItemCell("Pages/Hertz", cont, "Hertz", "herzt", 2, 1, 1, &ui.frequency);
    CreateItemCell("Pages/ServoCtrl", cont, "Servo", "volang", 0, 2, 1, &ui.ccpmservo);
    CreateItemCell("Pages/UARTViewer", cont, "UART", "terminal", 1, 2, 2, &ui.uartter);
    CreateItemCell("Pages/DAPLink", cont, "DAPLink", "daplink", 0, 3, 2, &ui.daplink);
    CreateItemCell("Pages/LogicAnalyzer", cont, "USB LA", "logic_analyzer", 2, 3, 1, &ui.logicanalyzer);
    CreateItemCell("Pages/CandleLight", cont, "CAN Bus", "canbus", 0, 4, 1, &ui.usbcanbus);
    CreateItemCell("Pages/PowerSupply", cont, "PD PPS", "power", 1, 4, 2, &ui.powerpd);
    CreateItemCell("Pages/KaitoKey", cont, "KEY", "key", 0, 5, 1, &ui.kaitokey);
    CreateItemCell("Pages/IMUSensor", cont, "IMU", "box3d", 1, 5, 1, &ui.imu);
    CreateItemCell("Pages/IMUSensor", cont, "Setting", "setting", 2, 5, 1, &ui.setting);
    CreateItemCell("Pages/PowerList", cont, "PowerList", "power", 0, 6, 1, &ui.powerlist);

    /*Tile2: appList menu */
    lv_obj_t *ui_tileApps = lv_tileview_add_tile(ui_tileView, 1, 0, LV_DIR_LEFT);
    /*Create a list*/
    lv_obj_t *list1 = lv_list_create(ui_tileApps);
    lv_obj_set_size(list1, 280, 240);
    lv_obj_center(list1);

    // lv_obj_set_style_pad_top(list1, 30, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(list1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_color(list1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(list1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(list1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_scrollbar_mode(list1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_pad_top(list1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(list1, 100, LV_PART_MAIN | LV_STATE_DEFAULT);

    /*Add apps to the list*/

    CreateItemList("Pages/AnalogViewer", list1, "Analog View", "analog", "Analog\n"
                                                                 "0 - 3300mV "
                                                                 "View signal\n",
                   &ui.analog);
    CreateItemList("Pages/ColorWheel", list1, "LED Control", "color", "Control LED\n"
                                                              "LED WS2812 "
                                                              "LED FullColor\n",
                   &ui.ledcolor);

    CreateItemList("Pages/Interval", list1, "Interval Time", "clock", "Signal duration \n"
                                                                 "Get pulse "
                                                                 "View delay\n",
                   &ui.timekeeper);
    CreateItemList("Pages/IICDiscovery", list1, "I2C Discovery", "i2cnetwork", "Scan Device\n"
                                                                     "Check version\n"
                                                                     "Read sensor\n",
                   &ui.i2cscan);
    CreateItemList("Pages/PowerSupply", list1, "PD PPS Power", "power", "Power Supply ADJ\n"
                                                                  "Support USB PPS\n",
                   &ui.powerpd);

    CreateItemList("Pages/ServoCtrl", list1, "Servo Control", "volang", "CCPM Servo / ESC\n"
                                                                "Consistency Master\n"
                                                                "V1.0.0",
                   &ui.ccpmservo);
    CreateItemList("Pages/UARTViewer", list1, "UART Viewer", "terminal", "UART Terminal \n"
                                                                  "Live view\n"
                                                                  "data on UART RX\n"
                                                                  "V1.2.2",
                   &ui.uartter);

    CreateItemList("Pages/DAPLink", list1, "DAPLink", "daplink", "DAP Link debugger\n"
                                                                 "V2.2.3\n"
                                                                 "USB UART\n",
                   &ui.daplink);
    CreateItemList("Pages/LogicAnalyzer", list1, "Logic Analyzer", "logic_analyzer", "Logic Analyzer\n"
                                                                             "USB SUMPS\n"
                                                                             "V2.2.3\n",
                   &ui.logicanalyzer);

    CreateItemList("Pages/CandleLight", list1, "CAN Viewer", "canbus", "USB to CAN\n"
                                                                    "CandleLight\n"
                                                                    "V2.2.3\n"
                                                                    "Socket CAN\n",
                   &ui.usbcanbus);
    CreateItemList("Pages/KaitoKey", list1, "Pass Key", "key", "KaitoKey\n"
                                                            "FIDO2 & U2F\n"
                                                            "Passwordless\n"
                                                            "V-30-08-2023\n",
                   &ui.kaitokey);

    CreateItemList("Pages/Hertz", list1, "Signal Generator", "herzt", "Signal Generator\n"
                                                                      "Cycle\n"
                                                                      "V2.2.3\n"
                                                                      "Frequency counter\n",
                   &ui.frequency);
    CreateItemList("Pages/IMUSensor", list1, "IMU Sensor", "box3d", "IMU Sensor\n"
                                                                    "3d Viewer\n"
                                                                    "V2.2.3\n",
                   &ui.imu);
    CreateItemList("Pages/IMUSensor", list1, "Setting", "setting", "Setting\n"
                                                                    "3d Viewer\n"
                                                                    "V2.2.3\n",
                   &ui.setting);
    CreateItemList("Pages/PowerList", list1, "PowerList", "power", "Setting\n"
                                                                   "3d Viewer\n"
                                                                   "V2.2.3\n",
                   &ui.powerlist);
}

void AppLumiaView::CreateItemList(const char *app_src, lv_obj_t *parent, const char *name, const char *img_src, const char *infor, item_t *item)
{

    lv_obj_t *obj;
    lv_obj_t *icon;
    lv_obj_t *label;


    obj = lv_btn_create(parent);
    item->btn = obj;
    lv_obj_remove_style_all(obj);
    lv_obj_set_width(obj, lv_pct(100));
    lv_obj_set_align(obj, LV_ALIGN_CENTER);
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(obj, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x0), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_PRESSED);
    lv_obj_set_style_bg_opa(obj, 50, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    label = lv_label_create(obj);
    item->labelInfo = label;
    lv_label_set_text(label, name);
    lv_obj_center(label);
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_set_x(label, 60);
    lv_obj_set_style_text_color(label, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("sf_compact_17"), LV_PART_MAIN | LV_STATE_DEFAULT);

    icon = lv_img_create(obj);
    item->icon = icon;
    lv_obj_set_x(icon, 8);
    lv_img_set_src(icon, ResourcePool::GetImage(img_src));
    lv_obj_set_width(icon, LV_SIZE_CONTENT);
    lv_obj_set_height(icon, LV_SIZE_CONTENT);
    lv_obj_set_align(label, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_color(icon, lv_color_hex(0x056cff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(icon, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(icon, lv_color_hex(0x056cff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(icon, 0, LV_PART_MAIN | LV_STATE_DEFAULT);


}

void AppLumiaView::CreateItemCell(const char *app_src, lv_obj_t *parent, const char *name, const char *img_src, int col, int row, int size, item_t *item)
{
    lv_obj_t *label;
    lv_obj_t *obj;
    lv_obj_t *icon;
    item->app_src = app_src;

    // printf("app src %s\r\n", app_src);
    obj = lv_btn_create(parent);
    item->btn_cell = obj;
    lv_obj_set_style_shadow_width(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(obj, 180, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0x056cff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_grid_cell(obj, LV_GRID_ALIGN_STRETCH, col, size, LV_GRID_ALIGN_STRETCH, row, 1);

    label = lv_label_create(obj);
    item->labelInfo = label;
    lv_label_set_text(label, name);
    lv_obj_center(label);
    lv_obj_set_align(label, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_set_x(label, -18);
    lv_obj_set_y(label, 12);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("sf_compact_15"), LV_PART_MAIN | LV_STATE_DEFAULT);
    icon = lv_img_create(obj);
    item->icon = icon;
    lv_img_set_src(icon, ResourcePool::GetImage(img_src));
    lv_obj_set_width(icon, LV_SIZE_CONTENT);
    lv_obj_set_height(icon, LV_SIZE_CONTENT);
    lv_obj_set_align(icon, LV_ALIGN_CENTER);
    lv_obj_add_flag(icon, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_clear_flag(icon, LV_OBJ_FLAG_SCROLLABLE);
}

void AppLumiaView::Delete()
{
    printf("AppLumiaView::Delete()\n");
}

