/* logic analyzer hal example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include "logic_analyzer_hal.h"
#include "logic_analyzer_ll.h"
#include "logic_analyzer_hi_level_interrupt.h"
#include "soc/soc.h"
#include "soc/dport_access.h"
#include "esp_log.h"
#include "string.h"
#include "rom/cache.h"
#include "esp_cache.h" //esp_mm
#include "esp_psram.h"

#define LA_TASK_STACK 2048
#define DMA_FRAME 4032

// frame buff & dma descripter
static la_frame_t la_frame = {
    .fb.buf = NULL,
    .fb.len = 0, // bytes *** one sample = 2 byte
    .dma = NULL};

static TaskHandle_t logic_analyzer_task_handle = 0; // main task handle
static int logic_analyzer_started = 0;              // flag start dma

esp_err_t logic_analyzer_get_hw_param(logic_analyzer_hw_param_t *hw)
{
#ifdef LA_HW_PSRAM
    if (esp_psram_is_initialized())
    {
        hw->available_psram = 1;
    }
    else
    {
        hw->available_psram = 0;
        hw->current_psram = 0;
    }
#else
    hw->available_psram = 0;
    hw->current_psram = 0;
#endif
    if (hw->current_psram > hw->available_psram)
    {
        hw->current_psram = hw->available_psram;
    }
    if (hw->current_psram < 0)
    {
        hw->current_psram = 0;
    }

    hw->max_channels = LA_HW_MAX_CHANNELS;
    hw->min_channels = LA_HW_MIN_CHANNELS;
    if (hw->current_channels > LA_HW_MAX_CHANNELS)
    {
        hw->current_channels = LA_HW_MAX_CHANNELS;
    }
    if (hw->current_channels < LA_HW_MIN_CHANNELS)
    {
        hw->current_channels = LA_HW_MIN_CHANNELS;
    }

    int max_ram = 0;
    if (hw->current_psram) // psram
    {
        max_ram = (int)heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM);
        if (hw->current_channels > 4)
        {
            hw->max_sample_rate = (hw->current_channels == 8 ? LA_HW_MAX_PSRAM_8_SAMPLE_RATE : LA_HW_MAX_PSRAM_16_SAMPLE_RATE);
            hw->min_sample_rate = (hw->current_channels == 8 ? LA_HW_MIN_8_SAMPLE_RATE : LA_HW_MIN_16_SAMPLE_RATE);
            hw->max_sample_cnt = (hw->current_channels == 8 ? max_ram : max_ram / 2);
            hw->min_sample_cnt = (hw->current_channels == 8 ? LA_HW_MIN_8_SAMPLE_CNT : LA_HW_MIN_16_SAMPLE_CNT);
        }
        else // channels = 4
        {
            hw->max_sample_rate = LA_HW_MAX_PSRAM_8_SAMPLE_RATE; // 4
            hw->min_sample_rate = LA_HW_MIN_8_SAMPLE_RATE;       // 4
            hw->max_sample_cnt = LA_HW_MAX_PSRAM_8_SAMPLE_CNT;   // 4
            hw->min_sample_cnt = LA_HW_MIN_8_SAMPLE_CNT;         // 4
        }
    }
    else // ram
    {
        max_ram = (int)heap_caps_get_largest_free_block(MALLOC_CAP_DMA);
        if (hw->current_channels > 4)
        {
            hw->max_sample_rate = (hw->current_channels == 8 ? LA_HW_MAX_RAM_8_SAMPLE_RATE : LA_HW_MAX_RAM_16_SAMPLE_RATE);
            hw->min_sample_rate = (hw->current_channels == 8 ? LA_HW_MIN_8_SAMPLE_RATE : LA_HW_MIN_16_SAMPLE_RATE);
            hw->max_sample_cnt = (hw->current_channels == 8 ? max_ram : max_ram / 2);
            hw->min_sample_cnt = (hw->current_channels == 8 ? LA_HW_MIN_8_SAMPLE_CNT : LA_HW_MIN_16_SAMPLE_CNT);
        }
        else
        {
            hw->max_sample_rate = LA_HW_MAX_RAM_8_SAMPLE_RATE; // 4
            hw->min_sample_rate = LA_HW_MIN_8_SAMPLE_RATE;     // 4
            hw->max_sample_cnt = LA_HW_MAX_RAM_8_SAMPLE_CNT;   // 4
            hw->min_sample_cnt = LA_HW_MIN_8_SAMPLE_CNT;       // 4
        }
    }
    return ESP_OK;
}

#ifdef CONFIG_IDF_TARGET_ESP32
//
// esp32 only
// sample sequence in 32 word - adr0=sample1, adr1=sample0
// swap sample sequence
//
static inline void swap_buf(uint16_t *buf, int cnt)
{
    uint16_t tmp;
    for (int i = 0; i < cnt; i += 2)
    {
        tmp = buf[i];
        buf[i] = buf[i + 1];
        buf[i + 1] = tmp;
    }
}
#endif

/**
 * @brief allocate dma descriptor
 *
 * @param uint32_t size - size of sample frame buffer (bytes)
 * @param uint8_t *buffer - pointer of sample frame buffer
 *
 * @return
 *     - dma descriptor ( NULL if no mem )
 */
static lldesc_t *allocate_dma_descriptors(uint32_t size, uint8_t *buffer)
{
    uint32_t count = size / DMA_FRAME;     //  dma frames count
    uint32_t last_size = size % DMA_FRAME; // last frame bytes

    lldesc_t *dma = (lldesc_t *)heap_caps_malloc((count + 1) * sizeof(lldesc_t), MALLOC_CAP_DMA);
    if (dma == NULL)
    {
        return dma;
    }
    int x = 0;
    for (; x < count; x++)
    {
        dma[x].size = DMA_FRAME;
        dma[x].length = DMA_FRAME;
        dma[x].sosf = 0;
        dma[x].eof = 0;
        dma[x].owner = 1;
        dma[x].buf = buffer + DMA_FRAME * x;
        dma[x].empty = (uint32_t)&dma[(x + 1)];
    }

    dma[x].size = last_size;
    dma[x].length = last_size;
    dma[x].sosf = 0;
    dma[x].eof = 1;
    dma[x].owner = 1;
    dma[x].buf = buffer + DMA_FRAME * x;
    dma[x].empty = 0;

    return dma;
}
/**
 *  @brief  full stop & free all
 */
static void logic_analyzer_stop(void)
{
    // stop dma transfer
    logic_analyzer_ll_stop();
    // deinit dma isr
    logic_analyzer_ll_deinit_dma_eof_isr();
    // free allocated mem
    if (la_frame.dma)
    {
        free(la_frame.dma);
        la_frame.dma = NULL;
    }
    if (la_frame.fb.buf)
    {
        free(la_frame.fb.buf);
        la_frame.fb.buf = NULL;
        la_frame.fb.len = 0;
    }
    // la status - stopped -> ready to new start
    logic_analyzer_started = 0;
}
/**
 *  @brief main logic analyzer task
 *       call callback function after dma transfer
 *       callback param = 0 if timeout or reset
 *  @param *arg - pointer to callback function from cfg
 */
static void logic_analyzer_task(void *arg)
{
    int noTimeout;
    logic_analyzer_config_t *cfg = (logic_analyzer_config_t *)arg;

    while (1)
    {
        noTimeout = ulTaskNotifyTake(pdFALSE, cfg->meashure_timeout); // portMAX_DELAY
        if (noTimeout)                                                // dma data ready
        {
            // dma data ready
#ifdef CONFIG_IDF_TARGET_ESP32
            // esp32 -> sample sequence in 32 word - adr0=sample1, adr1=sample0
            // swap sample sequence on esp32.
            swap_buf((uint16_t *)la_frame.fb.buf, la_frame.fb.len / (cfg->number_channels / 8)); // 16 channels only on esp32
#endif
            // synchronize cpu cache and psram after dma transfer, psram -> cache
            // !!Attention -> ESP_CACHE_MSYNC_FLAG_DIR_M2C defined on IDF version 5.2.X, current compile on master branch
#ifdef LA_HW_PSRAM
            if (cfg->samples_to_psram)
            {
                int err = esp_cache_msync(la_frame.fb.buf, la_frame.fb.len, ESP_CACHE_MSYNC_FLAG_DIR_M2C);
                if (err)
                    ESP_LOGE("CACHE", "ERR %x", err);
            }
#endif
            int l_samples = (cfg->number_channels > 4) ? (la_frame.fb.len / (cfg->number_channels / 8)) : la_frame.fb.len * 2; // (8/16)/(4)
            cfg->logic_analyzer_cb((uint8_t *)la_frame.fb.buf, l_samples, logic_analyzer_ll_get_sample_rate(cfg->sample_rate), cfg->number_channels);
            logic_analyzer_stop();
            vTaskDelete(logic_analyzer_task_handle);
        }
        else // timeout detected
        {
#ifdef CONFIG_ANALYZER_USE_HI_LEVEL_INTERRUPT
            ll_hi_level_triggered_isr_timeout_stop(); // restore gpio irq reg
#endif
            cfg->logic_analyzer_cb(NULL, 0, 0, 0); // timeout
            logic_analyzer_stop();
            vTaskDelete(logic_analyzer_task_handle);
        }
    }
}
/**
 * @brief Start logic analyzer
 *
 * @param config Configurations - see logic_analyzer_config_t struct
 *
 * @return
 *     - ESP_OK                 Success
 *     - ESP_ERR_INVALID_ARG    Parameter error
 *     - ESP_ERR_NO_MEM         No memory to initialize logic_analyzer
 *     - ESP_ERR_INVALID_STATE  Logic_analyzer already working
 *     - ESP_FAIL               Initialize fail
 */
esp_err_t start_logic_analyzer(logic_analyzer_config_t *config)
{
    esp_err_t ret = 0;
    logic_analyzer_hw_param_t hw_param;
    // runtime get HW params
    hw_param.current_channels = config->number_channels;
    hw_param.current_psram = config->samples_to_psram;
    logic_analyzer_get_hw_param(&hw_param);

    if (config->meashure_timeout == 0) // restart
    {
        if (logic_analyzer_started)
        {
#ifdef CONFIG_ANALYZER_USE_HI_LEVEL_INTERRUPT
            ll_hi_level_triggered_isr_timeout_stop(); // restore gpio irq reg
#endif
            config->logic_analyzer_cb(NULL, 0, 0, 0); // timeout or restart
            logic_analyzer_stop();                    // todo stop & clear on task or external ??
            vTaskDelete(logic_analyzer_task_handle);
        }
        else
        {
            config->logic_analyzer_cb(NULL, 0, 0, 0); // timeout or restart
        }
        ret = ESP_OK;
        goto _retcode;
    }
    // check la status
    if (logic_analyzer_started)
    {
        return ESP_ERR_INVALID_STATE;
    }
    logic_analyzer_started = 1;
    // check cb pointer
    if (config->logic_analyzer_cb == NULL)
    {
        goto _ret;
    }
    if (config->number_channels > hw_param.max_channels || config->number_channels < hw_param.min_channels)
    {
        goto _ret;
    }
    // check GPIO num - 0-MAX_GPIO or num < 0 // todo use macros to legal pin definition // now it controlled from WS headers
    for (int i = 0; i < config->number_channels; i++)
    {
        if (config->pin[i] > LA_HW_MAX_GPIO || config->pin[i] < LA_HW_MIN_GPIO)
        {
            goto _ret;
        }
    }
    if (config->pin_trigger > LA_HW_MAX_GPIO || config->pin_trigger < LA_HW_MIN_GPIO)
    {
        goto _ret;
    }
    // check intr edge
    else if ((config->trigger_edge >= 0 && config->trigger_edge < GPIO_INTR_MAX) == 0)
    {
        goto _ret;
    }
    // check sample rate
    if (config->sample_rate > hw_param.max_sample_rate || config->sample_rate < hw_param.min_sample_rate)
    {
        goto _ret;
    }
    // check number of samples
    if (config->number_of_samples > hw_param.max_sample_cnt || config->number_of_samples < hw_param.min_sample_cnt)
    {
        goto _ret;
    }
    // check psram mode
    if (config->samples_to_psram > hw_param.available_psram || config->samples_to_psram < 0)
    {
        goto _ret;
    }

    // allocate frame buffer
    uint32_t bytes_to_alloc = config->number_channels > 4 ? (config->number_of_samples * (config->number_channels / 8)) : (config->number_of_samples / 2);
    if (config->samples_to_psram == 0)
    {
        // alloc on RAM
        uint32_t largest_free_block = heap_caps_get_largest_free_block(MALLOC_CAP_DMA); // byte
        if (largest_free_block < bytes_to_alloc + ((bytes_to_alloc / DMA_FRAME) + 1) * sizeof(lldesc_t))
        {
            bytes_to_alloc = largest_free_block - ((bytes_to_alloc / DMA_FRAME) + 2) * sizeof(lldesc_t); // free space with dma lldesc size
        }
        ESP_LOGD("DMA HEAP Before", "All_dma_heap=%d Largest_dma_heap_block=%d", heap_caps_get_free_size(MALLOC_CAP_DMA), heap_caps_get_largest_free_block(MALLOC_CAP_DMA));
        la_frame.fb.len = bytes_to_alloc & ~0x3; // burst transfer word align
        la_frame.fb.buf = heap_caps_calloc(la_frame.fb.len, 1, MALLOC_CAP_DMA);
        //    la_frame.fb.buf = heap_caps_malloc(la_frame.fb.len, MALLOC_CAP_DMA);
        ESP_LOGD("DMA HEAP After", "All_dma_heap=%d Largest_dma_heap_block=%d", heap_caps_get_free_size(MALLOC_CAP_DMA), heap_caps_get_largest_free_block(MALLOC_CAP_DMA));
    }
    else
    {
        // alloc on PSRAM ->  todo check free ram for lldescr ???
        // PSRAM - only esp32s3 - 8/16 channels
        uint32_t largest_free_block = heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM);
        if (largest_free_block < bytes_to_alloc)
        {
            bytes_to_alloc = largest_free_block; // max free spiram
        }
        ESP_LOGD("DMA PSRAM HEAP Before", "All_dma_heap=%d Largest_dma_heap_block=%d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM), heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
        la_frame.fb.len = bytes_to_alloc & ~(GDMA_PSRAM_BURST - 1); // 16-32 bytes align
        //    la_frame.fb.buf = heap_caps_aligned_alloc(GDMA_PSRAM_BURST, la_frame.fb.len, MALLOC_CAP_SPIRAM);
        la_frame.fb.buf = heap_caps_aligned_calloc(GDMA_PSRAM_BURST, la_frame.fb.len, 1, MALLOC_CAP_SPIRAM);
        ESP_LOGD("DMA PSRAM HEAP After", "All_dma_heap=%d Largest_dma_heap_block=%d", heap_caps_get_free_size(MALLOC_CAP_SPIRAM), heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
    }
    if (la_frame.fb.buf == NULL)
    {
        ret = ESP_ERR_NO_MEM;
        goto _retcode;
    }
    ESP_LOGD("DMA HEAP", "Allocated %d bytes", la_frame.fb.len);
    //  allocate dma descriptor buffer
    la_frame.dma = allocate_dma_descriptors(la_frame.fb.len, la_frame.fb.buf);
    if (la_frame.dma == NULL)
    {
        ret = ESP_ERR_NO_MEM;
        goto _freebuf_ret;
    }
    // configure   - pin definition, pin trigger, sample frame & dma frame, clock divider
    logic_analyzer_ll_config(config->pin, config->sample_rate, config->number_channels, &la_frame);
    // start main task - check logic analyzer get data & call cb // todo -> test priority change
    if (pdPASS != xTaskCreate(logic_analyzer_task, "la_task", LA_TASK_STACK * 4, config, uxTaskPriorityGet(NULL) /*configMAX_PRIORITIES - 5*/, &logic_analyzer_task_handle))
    {
        ret = ESP_ERR_NO_MEM;
        goto _freedma_ret;
    }
    // init dma eof isr
    ret = logic_analyzer_ll_init_dma_eof_isr(logic_analyzer_task_handle);
    if (ret != ESP_OK)
    {
        goto _freetask_ret;
    }
    // start meashure
    if (config->pin_trigger < 0)
    {
        logic_analyzer_ll_start();
    }
    else // triggered start
    {
        logic_analyzer_ll_triggered_start(config->pin_trigger, config->trigger_edge);
    }
    return ESP_OK;

_freetask_ret:
    vTaskDelete(logic_analyzer_task_handle);
_freedma_ret:
    free(la_frame.dma);
_freebuf_ret:
    free(la_frame.fb.buf);
_retcode:
    logic_analyzer_started = 0;
    return ret;
_ret:
    logic_analyzer_started = 0;
    return ESP_ERR_INVALID_ARG;
}
