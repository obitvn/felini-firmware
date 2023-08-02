/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <cstdio>
#include "StatusBar.h"
#include "Common/DataProc/DataProc.h"

#define CONFIG_PLACE_NAME "obit test"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-function-type"

#define BATT_USAGE_HEIGHT (lv_obj_get_style_height(ui.battery.img, 0) - 6)
#define BATT_USAGE_WIDTH (lv_obj_get_style_width(ui.battery.img, 0) - 4)

#define STATUS_BAR_HEIGHT 22

static Account *actStatusBar;

static void StatusBar_AnimCreate(lv_obj_t *contBatt);

struct
{
    lv_obj_t *cont;

    lv_obj_t *msg;

    lv_obj_t *alarm;

    lv_obj_t *wifi;

    struct
    {
        lv_obj_t *location;
        lv_obj_t *label;
    } locate;

    lv_obj_t *imgSD;

    lv_obj_t *labelClock;

    struct
    {
        lv_obj_t *img;
        lv_obj_t *objUsage;
        lv_obj_t *label;
    } battery;
} ui;

static int onEvent(Account *account, Account::EventParam_t *param)
{
    if (param->event != Account::EVENT_NOTIFY)
    {
        return Account::ERROR_UNSUPPORTED_REQUEST;
    }

    if (param->size != sizeof(DataProc::StatusBar_Info_t))
    {
        return Account::ERROR_SIZE_MISMATCH;
    }

    // DataProc::StatusBar_Info_t *info = (DataProc::StatusBar_Info_t *)param->data_p;

    return 0;
}

static void StatusBar_ConBattSetOpa(lv_obj_t *obj, int32_t opa)
{
    lv_obj_set_style_opa(obj, opa, 0);
}

static void StatusBar_onAnimOpaFinish(lv_anim_t *a)
{
    lv_obj_t *obj = (lv_obj_t *)a->var;
    StatusBar_ConBattSetOpa(obj, LV_OPA_COVER);
    StatusBar_AnimCreate(obj);
}

static void StatusBar_onAnimHeightFinish(lv_anim_t *a)
{
    lv_anim_t a_opa;
    lv_anim_init(&a_opa);
    lv_anim_set_var(&a_opa, a->var);
    lv_anim_set_exec_cb(&a_opa, (lv_anim_exec_xcb_t)StatusBar_ConBattSetOpa);
    lv_anim_set_ready_cb(&a_opa, StatusBar_onAnimOpaFinish);
    lv_anim_set_values(&a_opa, LV_OPA_COVER, LV_OPA_TRANSP);
    lv_anim_set_early_apply(&a_opa, true);
    lv_anim_set_delay(&a_opa, 500);
    lv_anim_set_time(&a_opa, 500);
    lv_anim_start(&a_opa);
}

static void StatusBar_AnimCreate(lv_obj_t *contBatt)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, contBatt);
    lv_anim_set_exec_cb(&a, [](void *var, int32_t v)
                        { lv_obj_set_height((lv_obj_t *)var, v); });
    lv_anim_set_values(&a, 0, BATT_USAGE_HEIGHT);
    lv_anim_set_time(&a, 1000);
    lv_anim_set_ready_cb(&a, StatusBar_onAnimHeightFinish);
    lv_anim_start(&a);
}

static void StatusBar_Update(lv_timer_t *timer)
{
    /* clock */
    HAL::Clock_Info_t clock;
    actStatusBar->Pull("Clock", &clock, sizeof(clock));
    lv_label_set_text_fmt(ui.labelClock, "%02d:%02d", clock.hour, clock.minute);

    /* battery */
    HAL::PowerPMIC_Info_t power;
    actStatusBar->Pull("Power", &power, sizeof(power));
    lv_label_set_text_fmt(ui.battery.label, "%d", power.usage);

    // Charging has problem
    bool Is_BattCharging = power.isCharging;
    lv_obj_t *contBatt = ui.battery.objUsage;
    static bool Is_BattChargingAnimActive = false;
    if (Is_BattCharging)
    {
        if (!Is_BattChargingAnimActive)
        {
            StatusBar_AnimCreate(contBatt);
            Is_BattChargingAnimActive = true;
        }
    }
    else
    {
        if (Is_BattChargingAnimActive)
        {
            lv_anim_del(contBatt, nullptr);
            StatusBar_ConBattSetOpa(contBatt, LV_OPA_COVER);
            Is_BattChargingAnimActive = false;
        }
        if (power.usage < 20)
        {
            lv_img_set_src(ui.battery.img, ResourcePool::GetImage("battery_red"));
        }
        else
        {
            lv_coord_t height = lv_map(power.usage, 0, 100, 0, BATT_USAGE_HEIGHT);
            lv_obj_set_height(contBatt, height);
        }
    }
}

static lv_obj_t *StatusBar_Create(lv_obj_t *par)
{
    lv_obj_t *cont = lv_obj_create(par);
    lv_obj_remove_style_all(cont);

    lv_obj_set_size(cont, LV_HOR_RES, STATUS_BAR_HEIGHT);
    lv_obj_set_y(cont, -STATUS_BAR_HEIGHT);

    /* style1 */
    lv_obj_set_style_bg_opa(cont, LV_OPA_TRANSP, LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(cont, lv_color_hex(0x333333), LV_STATE_DEFAULT);

    /* style2 */
    lv_obj_set_style_bg_opa(cont, LV_OPA_60, LV_STATE_USER_1);
    lv_obj_set_style_bg_color(cont, lv_color_black(), LV_STATE_USER_1);
    lv_obj_set_style_shadow_color(cont, lv_color_black(), LV_STATE_USER_1);
    lv_obj_set_style_shadow_width(cont, 10, LV_STATE_USER_1);

    static lv_style_transition_dsc_t tran;
    static const lv_style_prop_t prop[] = {
        LV_STYLE_BG_COLOR,
        LV_STYLE_OPA,
        LV_STYLE_PROP_INV};
    lv_style_transition_dsc_init(
        &tran,
        prop,
        lv_anim_path_ease_out,
        200,
        0,
        nullptr);
    lv_obj_set_style_transition(cont, &tran, LV_STATE_USER_1);

    ui.cont = cont;

    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, lv_color_white());
    lv_style_set_text_font(&style, ResourcePool::GetFont("alibabasans_regular_13"));

    /* message */
    lv_obj_t *img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("message"));
    lv_obj_align(img, LV_ALIGN_LEFT_MID, 5, 0);
    ui.msg = img;

    /* alarm */
    img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("alarm"));
    lv_obj_align_to(img, ui.msg, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    ui.alarm = img;

    /* locate */
    img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("location"));
    lv_obj_align_to(img, ui.alarm, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    ui.locate.location = img;

    lv_obj_t *label = lv_label_create(cont);
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, (char *)CONFIG_PLACE_NAME);
    lv_obj_align_to(label, ui.locate.location, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
    ui.locate.label = label;

    /* clock */
    label = lv_label_create(cont);
    lv_obj_add_style(label, &style, 0);
    lv_label_set_text(label, "00:00");
    lv_obj_center(label);
    ui.labelClock = label;

    /* battery */
    img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("battery"));
    lv_obj_align(img, LV_ALIGN_RIGHT_MID, -30, 0);
    lv_img_t *img_ext = (lv_img_t *)img;
    lv_obj_set_size(img, img_ext->w, img_ext->h);
    ui.battery.img = img;

    /* wifi */
    img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("wifi_connect"));
    lv_obj_align_to(img, ui.battery.img, LV_ALIGN_OUT_LEFT_MID, -3, 0);
    ui.wifi = img;

    /* sd card */
    img = lv_img_create(cont);
    lv_img_set_src(img, ResourcePool::GetImage("sd_card"));
    lv_obj_align_to(img, ui.wifi, LV_ALIGN_OUT_LEFT_MID, -3, 0);
    ui.imgSD = img;

    lv_obj_t *obj = lv_obj_create(img);
    lv_obj_remove_style_all(obj);
    lv_obj_set_style_bg_color(obj, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_style_opa(obj, LV_OPA_COVER, 0);
    lv_obj_set_size(obj, BATT_USAGE_WIDTH, BATT_USAGE_HEIGHT);
    lv_obj_align(obj, LV_ALIGN_BOTTOM_MID, 0, -2);
    ui.battery.objUsage = obj;

    label = lv_label_create(cont);
    lv_obj_add_style(label, &style, 0);
    lv_obj_align_to(label, ui.battery.img, LV_ALIGN_OUT_RIGHT_MID, 2, 2);
    lv_label_set_text(label, "100%");
    ui.battery.label = label;

    StatusBar::SetStyle(StatusBar::STYLE_TRANSP);

    lv_timer_t *timer = lv_timer_create(StatusBar_Update, 1000, nullptr);
    lv_timer_ready(timer);

    return ui.cont;
}

void StatusBar::SetStyle(Style_t style)
{
    lv_obj_t *cont = ui.cont;
    if (style == STYLE_TRANSP)
    {
        lv_obj_add_state(cont, LV_STATE_DEFAULT);
        lv_obj_clear_state(cont, LV_STATE_USER_1);
    }
    else if (style == STYLE_BLACK)
    {
        lv_obj_add_state(cont, LV_STATE_USER_1);
    }
    else
    {
        return;
    }
}

void StatusBar::Init(lv_obj_t *par)
{
    StatusBar_Create(par);
}

// 一定要记得初始化！！！  => DP_LIST.inc
DATA_PROC_INIT_DEF(StatusBar)
{
    account->Subscribe("PowerPMIC");
    account->Subscribe("Clock");
    account->SetEventCallback(onEvent);

    actStatusBar = account;
}

void StatusBar::Appear(bool en)
{
    int32_t start = -STATUS_BAR_HEIGHT;
    int32_t end = 0;

    if (!en)
    {
        int32_t temp = start;
        start = end;
        end = temp;
    }

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, ui.cont);
    lv_anim_set_values(&a, start, end);
    lv_anim_set_time(&a, 500);
    lv_anim_set_delay(&a, 1000);
    lv_anim_set_exec_cb(&a, LV_ANIM_EXEC(y));
    lv_anim_set_path_cb(&a, lv_anim_path_ease_out);
    lv_anim_set_early_apply(&a, true);
    lv_anim_start(&a);
}

#pragma GCC diagnostic pop
