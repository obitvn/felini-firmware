#include "LogicAnalyzerView.h"
#include <cstdio>

using namespace Page;


void LogicAnalyzerView::Create(lv_obj_t *root)
{
    lv_obj_set_style_border_width(root, 0, LV_PART_MAIN);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);


}




void LogicAnalyzerView::Delete()
{
    printf("LogicAnalyzerView::Delete()");
}

