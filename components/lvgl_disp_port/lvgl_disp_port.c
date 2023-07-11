#include "lvgl_disp_port.h"
#include "esp_heap_caps.h"


static SemaphoreHandle_t lvgl_mutex = NULL;


static IRAM_ATTR void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

static void lv_tick_task(void *arg)
{
    (void) arg;

    lv_tick_inc(portTICK_PERIOD_MS);
}

// Profile fun! microseconds to seconds
double GetTime() { return (double)lv_tick_get() * 1000; }

int RamTest()
    {
    int rs[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4000 };
    printf("Ram Speed Test!\n\n");
    char xx = 0;
    for (int a = 0; a < 13; a++)
        {
            printf("Read Speed 8bit ArraySize %4dkb ", rs[a]);
            int ramsize = rs[a] * 1024;
            char * rm = (char*)heap_caps_malloc(ramsize, MALLOC_CAP_SPIRAM);

            int iters = 10; // Just enuff to boot the dog
            if (rs[a] < 512) iters = 50;
            double st = GetTime();
            for (int b = 0; b < iters; b++)
                for (int c = 0; c < ramsize; c++)
                {
                    rm[c] = b;
                    xx |= rm[c];
                }
            st = GetTime() - st;
            vTaskDelay(1); // Dog it!
            double speed = ((double)(iters*ramsize ) / (1024 * 1024)) / (st);
            printf(" time: %2.1f %2.1f mb/sec  \n", st, speed);
            heap_caps_free(rm);
        }
    printf("\n");
    for (int a = 0; a < 13; a++)
        {
        printf("Read Speed 16bit ArraySize %4dkb ", rs[a]);
        int ramsize = rs[a] * 1024;
        short * rm = (short*)heap_caps_malloc(ramsize, MALLOC_CAP_SPIRAM);

        int iters = 10; // Just enuff to boot the dog
        if (rs[a] < 512) iters = 50;
        double st = GetTime();
        for (int b = 0; b < iters; b++)
            for (int c = 0; c < ramsize/2; c++)
                xx |= rm[c];
        st = GetTime() - st;
        vTaskDelay(1); // Dog it!
        double speed = ((double)(iters*ramsize) / (1024 * 1024)) / (st);
        printf(" time: %2.1f %2.1f mb/sec  \n", st, speed);
        heap_caps_free(rm);
        }
    printf("\n");
    for (int a = 0; a < 13; a++)
        {
        printf("Read Speed 32bit ArraySize %4dkb ", rs[a]);
        int ramsize = rs[a] * 1024;
        int * rm = (int*)heap_caps_malloc(ramsize, MALLOC_CAP_SPIRAM);

        int iters = 10; // Just enuff to boot the dog
        if (rs[a] < 512) iters = 50;
        double st = GetTime();
        for (int b = 0; b < iters; b++)
            for (int c = 0; c < ramsize/4; c++)
                xx |= rm[c];
        st = GetTime() - st;
        vTaskDelay(1); // Dog it!
        double speed = ((double)(iters*ramsize) / (1024 * 1024)) / (st);
        printf(" time: %2.1f %2.1f mb/sec  \n", st, speed);
        heap_caps_free(rm);
        }
    printf("Test done!\n");
    return xx;
    }

static lv_disp_draw_buf_t disp_buf;    

void lv_port_disp_init(void)
{
    lvgl_mutex = xSemaphoreCreateMutex();

    // RamTest();
    // heap_caps_dump_all();
    lvgl_driver_init();

    static lv_color_t *lv_buf =  NULL;
    lv_color_t* buf_1 = heap_caps_malloc(DISP_BUF_SIZE*2,  MALLOC_CAP_DMA);
    assert(buf_1 != NULL);

    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, DISP_BUF_SIZE);




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