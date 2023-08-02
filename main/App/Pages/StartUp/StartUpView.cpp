#include "StartUpView.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
#pragma GCC diagnostic ignored "-Wcast-function-type"

using namespace Page;

#define COLOR_ORANGE lv_color_hex(0x4682B4)

void StartupView::Create(lv_obj_t *root)
{
    lv_obj_remove_style_all(root);
    lv_obj_set_size(root, LV_HOR_RES, LV_VER_RES);

    lv_obj_t *cont_bg = lv_obj_create(root);
    lv_obj_remove_style_all(cont_bg);
    lv_obj_set_size(cont_bg, 280, 280);
    lv_obj_clear_flag(cont_bg, LV_OBJ_FLAG_SCROLLABLE); /// Flags
    lv_obj_set_style_border_opa(root, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(cont_bg, ResourcePool::GetImage("catb"), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_center(cont_bg);

    lv_obj_t *cont = lv_obj_create(root);
    lv_obj_remove_style_all(cont);
    lv_obj_clear_flag(cont, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(cont, 220, 50);
    lv_obj_set_style_border_color(cont, COLOR_ORANGE, 0);
    lv_obj_set_style_border_side(cont, LV_BORDER_SIDE_BOTTOM, 0);
    lv_obj_set_style_border_width(cont, 3, 0);
    lv_obj_set_style_border_post(cont, true, 0);
    lv_obj_center(cont);
    ui.cont = cont;

    // lv_obj_t *ui_Image1 = lv_img_create(cont);
    // lv_img_set_src(ui_Image1, ResourcePool::GetImage("catb"));
    // lv_obj_set_width(ui_Image1, LV_SIZE_CONTENT);  /// 1
    // lv_obj_set_height(ui_Image1, LV_SIZE_CONTENT); /// 1
    // lv_obj_set_align(ui_Image1, LV_ALIGN_CENTER);
    // lv_obj_add_flag(ui_Image1, LV_OBJ_FLAG_ADV_HITTEST);  /// Flags
    // lv_obj_clear_flag(ui_Image1, LV_OBJ_FLAG_SCROLLABLE); /// Flags


    lv_obj_t *label = lv_label_create(cont);
    lv_obj_set_style_text_font(label, ResourcePool::GetFont("alibabasans_regular_32"), 0);
    lv_obj_set_style_text_color(label, lv_color_white(), 0);
    lv_label_set_text(label, "Tien Thinh");
    lv_obj_center(label);
    ui.labelLogo = label;

    ui.anim_timeline = lv_anim_timeline_create();

#define ANIM_DEF(start_time, obj, attr, start, end) \
    {start_time, obj, LV_ANIM_EXEC(attr), start, end, 500, lv_anim_path_ease_out, true}

    lv_anim_timeline_wrapper_t wrapper[] =
        {
            ANIM_DEF(0, ui.cont, width, 0, lv_obj_get_style_width(ui.cont, 0)),
            ANIM_DEF(500, ui.labelLogo, y, lv_obj_get_style_height(ui.cont, 0), lv_obj_get_y(ui.labelLogo)),
            LV_ANIM_TIMELINE_WRAPPER_END};

    lv_anim_timeline_add_wrapper(ui.anim_timeline, wrapper);
}

void StartupView::Delete()
{
    if (ui.anim_timeline)
    {
        lv_anim_timeline_del(ui.anim_timeline);
        ui.anim_timeline = nullptr;
    }
}

#pragma GCC diagnostic pop