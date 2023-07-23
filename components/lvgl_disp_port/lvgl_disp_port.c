#include "lvgl_disp_port.h"
#include "esp_heap_caps.h"
#include "st7789v.h"
#include "esp_timer.h"

static SemaphoreHandle_t lvgl_mutex = NULL;


static IRAM_ATTR void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

// static void lv_tick_task(void *arg)
// {
//     (void) arg;

//     lv_tick_inc(portTICK_PERIOD_MS);
// }

static void lv_tick_task(void *arg) {
  (void)arg;

  lv_tick_inc(1);
}


static void disp_init(void);

static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                       lv_color_t *color_p);

static lv_disp_draw_buf_t disp_buf;    

void lv_port_disp_init(void)
{
    lvgl_mutex = xSemaphoreCreateMutex();

 
    disp_init();

    static lv_color_t *lv_buf =  NULL;
    lv_color_t* buf_1 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t),  MALLOC_CAP_SPIRAM);
    assert(buf_1 != NULL);
    // lv_color_t* buf_2 = heap_caps_malloc(DISP_BUF_SIZE * sizeof(lv_color_t),  MALLOC_CAP_SPIRAM);
    // assert(buf_2 != NULL);

    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, DISP_BUF_SIZE);
    // lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, DISP_BUF_SIZE);

    /* 创建显示器 */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;
    disp_drv.hor_res = LV_HOR_RES_MAX;
    disp_drv.ver_res = LV_VER_RES_MAX;
    // disp_drv.full_refresh = 1;
    lv_disp_drv_register(&disp_drv);

    // heap_caps_dump_all();

    // esp_register_freertos_tick_hook((void *)lv_tick_task);
    const esp_timer_create_args_t periodic_timer_args = {
      .callback = &lv_tick_task, .name = "periodic_gui"};
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, 1 * 1000));

    // clear screen
    static lv_style_t style_screen;
    lv_style_init(&style_screen);
    lv_style_set_bg_color(&style_screen, lv_color_hex(0));
    lv_obj_add_style(lv_scr_act(), &style_screen,_LV_STYLE_STATE_CMP_SAME);
    disp_task_create();
    vTaskDelay(pdMS_TO_TICKS(100));
    st7789v_backlight_set(500); // 50%
}

static void gui_task(void *pvParameter)
{

    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1));

        if(pdTRUE == xSemaphoreTake(lvgl_mutex, portMAX_DELAY))
        {
            lv_task_handler();
            xSemaphoreGive(lvgl_mutex);
        }
    }
}

void disp_task_create(void)
{
    xTaskCreatePinnedToCore(gui_task, "disp task", 1024*32, NULL, 1, NULL, 1);
}

esp_err_t lv_port_sem_take(void)
{
    return !xSemaphoreTake(lvgl_mutex, portMAX_DELAY);
}

esp_err_t lv_port_sem_give(void)
{
    return !xSemaphoreGive(lvgl_mutex);
}



/*Initialize your display and the required peripherals.*/
static void disp_init(void) { st7789v_init(); }

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called
 * by LVGL
 */
void disp_enable_update(void) { disp_flush_enabled = true; }

/* Disable updating the screen (the flushing process) when disp_flush() is
 * called by LVGL
 */
void disp_disable_update(void) { disp_flush_enabled = false; }

/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the
 *background but 'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area,
                       lv_color_t *color_p) {
  if (disp_flush_enabled) {
    /*The most simple case (but also the slowest) to put all pixels to the
     * screen one-by-one*/
    st7789v_flush(area->x1, area->x2, area->y1, area->y2, (void *)color_p);
  }

  /*IMPORTANT!!!
   *Inform the graphics library that you are ready with the flushing*/
  lv_disp_flush_ready(disp_drv);
}