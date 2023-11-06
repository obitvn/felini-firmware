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
    // lv_color_t* buf_2 = (lv_color_t*)heap_caps_malloc(240 * 280 * 2,  MALLOC_CAP_SPIRAM  | MALLOC_CAP_8BIT);
    // assert(buf_2 != NULL);

    memset(buf_1, 0, 240 * 280 * 2);
    // memset(buf_2, 0, 240 * 280 * 2);

    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, 240 * 280);

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


/*Initialize your display and the required peripherals.*/
static void disp_init(void) 
{
    lcd.setBrightness(0);
    lcd.init(); // Initialize LovyanGFX
    lcd.setBrightness(0);
    lcd.fillScreen(TFT_BLACK);
    lcd.setColorDepth(16);
    lcd.setBrightness(50);
    
}

volatile bool disp_flush_enabled = true;
volatile uint32_t time_now=0, time_old=0;

const uint8_t frInIdleModeHz[] = {
    119, // RTNB 00h
    111, // RTNB 01h
    105, // RTNB 02h
    99,  // RTNB 03h
    94,  // RTNB 04h
    90,  // RTNB 05h
    86,  // RTNB 06h
    82,  // RTNB 07h
    78,  // RTNB 08h
    75,  // RTNB 09h
    72,  // RTNB 0Ah
    69,  // RTNB 0Bh
    67,  // RTNB 0Ch
    64,  // RTNB 0Dh
    62,  // RTNB 0Eh
    60,  // RTNB 0Fh
    58,  // RTNB 10h
    57,  // RTNB 11h
    55,  // RTNB 12h
    53,  // RTNB 13h
    52,  // RTNB 14h
    50,  // RTNB 15h
    49,  // RTNB 16h
    48,  // RTNB 17h
    46,  // RTNB 18h
    45,  // RTNB 19h
    44,  // RTNB 1Ah
    43,  // RTNB 1Bh
    42,  // RTNB 1Ch
    41,  // RTNB 1Dh
    40,  // RTNB 1Eh
    39   // RTNB 1Fh
};

uint8_t findNearestValueIndex(uint8_t value)
{
    uint8_t nearestIndex = 0;
    uint8_t nearestDifference = abs(value - frInIdleModeHz[0]);

    for (uint8_t i = 1; i < sizeof(frInIdleModeHz) / sizeof(frInIdleModeHz[0]); i++)
    {
        uint8_t difference = abs(value - frInIdleModeHz[i]);
        if (difference < nearestDifference)
        {
            nearestIndex = i;
            nearestDifference = difference;
        }
    }

    return nearestIndex;
}

void spicommand(uint8_t cmd, uint8_t data)
{
    lcd.writeCommand(cmd); // Read, issue command
    lcd.writeData(data);    // Read, issue argument

}

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

    time_now = lv_tick_get();

    float time_diff = (float)(time_now - time_old)/ 1000;
    float freq = (1/time_diff);

    // printf("freq %f timediff %f\r\n", freq, time_diff);

    spicommand(0xC6, findNearestValueIndex((uint8_t)freq) +45);

    lcd.startWrite();
    lcd.setAddrWindow(area->x1, area->y1, w, h);
    lcd.pushColors((uint16_t *)&color_p->full, w * h, true);
    lcd.endWrite();
    lv_disp_flush_ready(disp_drv);

    time_old = time_now;

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
}