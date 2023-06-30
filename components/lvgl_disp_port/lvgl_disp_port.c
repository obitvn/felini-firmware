#include "lvgl_disp_port.h"
#include "esp_heap_caps.h"


static SemaphoreHandle_t lvgl_mutex = NULL;




static void lv_tick_task(void *arg)
{
    (void) arg;

    lv_tick_inc(portTICK_PERIOD_MS);
}

void lv_port_disp_init(void)
{
    lvgl_mutex = xSemaphoreCreateMutex();

    lvgl_driver_init();

    /* 创建显示缓存 */
    static lv_disp_draw_buf_t disp_buf;
    static lv_color_t *lv_buf = NULL;
    static lv_color_t *lv_buf_1 = NULL;
    static lv_color_t *lv_buf_2 = NULL;


    lv_buf = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    assert(lv_buf != NULL);

    
    // lv_buf_1 = (lv_color_t *)heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    // assert(lv_buf_1 != NULL);

    // lv_buf_2 = (lv_color_t *)heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    // assert(lv_buf_2 != NULL);

    // lv_disp_draw_buf_init(&disp_buf, lv_buf_1, lv_buf_2, DISP_BUF_SIZE);

    lv_disp_draw_buf_init(&disp_buf, lv_buf, NULL, DISP_BUF_SIZE);

    /* 创建显示器 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    // disp_drv.full_refresh = 1;
    lv_disp_drv_register(&disp_drv);

    esp_register_freertos_tick_hook((void *)lv_tick_task);
    disp_task_create();
}

static void gui_task(void *pvParameter)
{

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));

        // if(pdTRUE == xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        // {
            lv_task_handler();
            xSemaphoreGive(lvgl_mutex);
        // }
    }
}

void disp_task_create(void)
{
    xTaskCreatePinnedToCore(gui_task, "disp task", 8192*10, NULL, configMAX_PRIORITIES-1, NULL, 1);
}

