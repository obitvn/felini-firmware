#include "lvgl_disp_port.hpp"
#include "esp_heap_caps.h"
#include "esp_timer.h"

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "conf_ESP32S3_ST7789.h"

static LGFX lcd; // declare display variable

static SemaphoreHandle_t lvgl_mutex = NULL;

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

    lv_color_t *buf_1 = (lv_color_t *)heap_caps_malloc(240 * 280 * 2, MALLOC_CAP_SPIRAM | MALLOC_CAP_8BIT);
    assert(buf_1 != NULL);
    lv_color_t* buf_2 = (lv_color_t*)heap_caps_malloc(240 * 280 * 2,  MALLOC_CAP_SPIRAM  | MALLOC_CAP_8BIT);
    assert(buf_2 != NULL);

    memset(buf_1, 0, 240 * 280 * 2);
    memset(buf_2, 0, 240 * 280 * 2);

    lv_disp_draw_buf_init(&disp_buf, buf_1, buf_2, 240 * 280);

    /* Create display */
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;
    disp_drv.hor_res = 280;
    disp_drv.ver_res = 240;
    disp_drv.full_refresh = 1;
    lv_disp_drv_register(&disp_drv);
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

    xTaskCreatePinnedToCore(gui_task, "disp task", 1024*8, NULL, 2, NULL, 1);

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
static void disp_init(void) 
{ 
    // st7789v_init();
    lcd.init(); // Initialize LovyanGFX
    lcd.setColorDepth(24);
    lcd.fillScreen(TFT_DARKCYAN);
    vTaskDelay(pdMS_TO_TICKS(100));
    lcd.fillScreen(TFT_VIOLET);
    vTaskDelay(pdMS_TO_TICKS(100));
    lcd.fillScreen(TFT_ORANGE);
    vTaskDelay(pdMS_TO_TICKS(100));
    lcd.fillScreen(TFT_RED);
    vTaskDelay(pdMS_TO_TICKS(100));
    lcd.fillScreen(TFT_BLUE);
    vTaskDelay(pdMS_TO_TICKS(100));
    lcd.fillScreen(TFT_GREEN);
    vTaskDelay(pdMS_TO_TICKS(100));
}

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
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t *disp_drv, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lcd.endWrite();
    // }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}