#include "lvgl_disp_port.h"
#include "esp_heap_caps.h"


static SemaphoreHandle_t lvgl_mutex = NULL;


static IRAM_ATTR void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

static void lv_tick_task(void *arg)
{
    (void) arg;

    lv_tick_inc(portTICK_PERIOD_MS);
}

static lv_disp_draw_buf_t disp_buf;    

void lv_port_disp_init(void)
{
    lvgl_mutex = xSemaphoreCreateMutex();

 
    // heap_caps_dump_all();
    lvgl_driver_init();

    static lv_color_t *lv_buf =  NULL;
    lv_color_t* buf_1 = heap_caps_malloc(DISP_BUF_SIZE*2,  MALLOC_CAP_SPIRAM);
    assert(buf_1 != NULL);
    lv_color_t* buf_2 = heap_caps_malloc(DISP_BUF_SIZE*2,  MALLOC_CAP_SPIRAM);
    assert(buf_2 != NULL);

    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISP_BUF_SIZE);




    /* 创建显示器 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = disp_driver_flush;
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    // disp_drv.full_refresh = 1;
    lv_disp_drv_register(&disp_drv);

    // heap_caps_dump_all();

    esp_register_freertos_tick_hook((void *)lv_tick_task);
    disp_task_create();
}

static void gui_task(void *pvParameter)
{

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(10));

        if(pdTRUE == xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(lvgl_mutex);
        }
    }
}

void disp_task_create(void)
{
    xTaskCreatePinnedToCore(gui_task, "disp task", 1024*16, NULL, 1, NULL, 1);
}

esp_err_t lv_port_sem_take(void)
{
    return !xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
}

esp_err_t lv_port_sem_give(void)
{
    return !xSemaphoreGive(lvgl_mutex);
}

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{   
    // lv_port_sem_take();

    disp_driver_flush(disp_drv, area, (uint8_t *)color_p);
    lv_disp_flush_ready(disp_drv);
    // lv_port_sem_give();
}