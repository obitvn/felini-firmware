#include "TemplateView.h"
#include <stdarg.h>
#include <stdio.h>

using namespace Page;

void TemplateView::Create(lv_obj_t* root)
{
    lv_obj_t* label = lv_label_create(root);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    lv_label_set_text(label, "");
    lv_obj_set_style_text_color(label, LV_COLOR_MAKE16(0xff, 0xff, 0xff), _LV_STYLE_STATE_CMP_SAME);
    ui.labelTitle = label;

    label = lv_label_create(root);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("alibabasans_regular_60"), 0);
    lv_label_set_text(label, "Page -1");
    lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
    lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(label, LV_COLOR_MAKE16(0xff, 0xff, 0xff), _LV_STYLE_STATE_CMP_SAME);
    ui.labelTick = label;
}
