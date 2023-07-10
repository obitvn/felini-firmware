#include "IICDiscoveryView.h"
#include <cstdio>

using namespace Page;


void IICDiscoveryView::Create(lv_obj_t *root)
{
    lv_obj_remove_style_all(root);
    /*Change the active screen's background color*/
    lv_obj_set_style_bg_color(root, lv_color_hex(0), LV_PART_MAIN);

    /*Create a white label, set its text and align it to the center*/
    lv_obj_t *label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Hello world");
    lv_obj_set_style_text_color(lv_scr_act(), lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
}




void IICDiscoveryView::Delete()
{
    printf("IICDiscoveryView::Delete()");
}

