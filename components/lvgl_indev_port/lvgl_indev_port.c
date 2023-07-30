#include "lvgl_indev_port.h"

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void touch_init(void);
static void touch_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

lv_indev_t *indev_encoder;
lv_indev_t *indev_touch;
lv_group_t * group;

lv_group_t * group_touch;

void lv_port_indev_init(void)
{
    static lv_indev_drv_t indev_drv;
    static lv_indev_drv_t touch_drv;

    encoder_init();
    touch_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_ENCODER;
    indev_drv.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv);

    /*Register a touch input device*/
    lv_indev_drv_init(&touch_drv);
    touch_drv.type = LV_INDEV_TYPE_POINTER;
    touch_drv.read_cb = touch_read;
    indev_touch = lv_indev_drv_register(&touch_drv);

    group = lv_group_create();
    lv_indev_set_group(indev_encoder, group);
    lv_group_set_default(group);
}

static void encoder_init(void)
{
    encoder_config();
}

static void touch_init(void)
{
    touch_driver_init();
}


uint32_t timeout=0;

static void touch_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    if(is_touched())
    {
        touch_driver_read(indev_drv, data);
        data->state = LV_INDEV_STATE_PR;
        if(data->key == LV_KEY_DOWN)
        {
            encoder_set_diff(-1);
        }
        if (data->key == LV_KEY_UP)
        {
            encoder_set_diff(1);
        }
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
        data->point.x = 0;
        data->point.y = 0;
    }
}


static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static bool last_state;

    data->enc_diff = encoder_get_diff();

    bool is_push = encoder_get_is_push();
    data->state = is_push ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;

    if(is_push != last_state)
    {
        last_state = is_push;
    }

    // if(encoder_get_is_push() == 1)
    // {
    //     timeout++;
    //     if(timeout>100)
    //     {
    //         //shut down
    //         printf("shut down");
    //         gpio_set_level((gpio_num_t)12, 0);
    //         gpio_set_level((gpio_num_t)12, 0);
    //         gpio_set_level((gpio_num_t)12, 0);
    //     }
    // }
    // else
    // {
    //     timeout = 0;
    // }
}

lv_indev_t* get_indev(void)
{
    return indev_encoder;
}

lv_group_t* get_group(void)
{
    return group;
}