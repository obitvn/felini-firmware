#pragma once

#include "logic_analyzer_const_definition.h"
#include "logic_analyzer_pin_definition.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Data structure of logic analyzer frame buffer
     */
    typedef struct
    {
        uint8_t *buf; // Pointer to the sample data
        size_t len;   // Length of the buffer in bytes
    } la_fb_t;

    typedef struct
    {
        la_fb_t fb;
        lldesc_t *dma; // Pointer of dma frame
    } la_frame_t;

    /**
     *  @brief logic analyzer config i2s
     *        configure all i2s struct,before stert
     *
     *  @param- int data_pins   - pointer of data GPIO array pin[16] ( 0-15 )
     *  @param- int pin_trigger - trigger GPIO ( -1 disable )
     *  @param- int sample_rate - real sample rate in HZ
     *  @param- la_frame_t *frame - pointer of dma frame ( dma desriptor, sample buffer, sample buffer len )
     *
     *  @return
     */
    void logic_analyzer_ll_config(int *data_pins, int sample_rate, int channels, la_frame_t *frame);
    /**
     *  @brief logic analyzer start meashure
     *
     */
    void logic_analyzer_ll_start();

    void logic_analyzer_ll_triggered_start(int pin_trigger, int trigger_edge);

    /**
     *  @brief logic analyzer stop meashure
     *
     */
    void logic_analyzer_ll_stop();
    /**
     *  @brief logic analyzer init dma eof isr
     *          isr after full dma transfer
     *  @param-  TaskHandle_t task  - notify main task after full dma transfer
     *
     *  @return
     */
    esp_err_t logic_analyzer_ll_init_dma_eof_isr(TaskHandle_t task);
    /**
     *  @brief logic analyzer free dma eof isr
     *
     *  @return
     */
    void logic_analyzer_ll_deinit_dma_eof_isr();
    /**
     *  @brief logic analyzer return real sample rate
     *
     *  @param  int sample_rate  - config sample rate
     *
     *  @return  real sample rate
     */
    int logic_analyzer_ll_get_sample_rate(int sample_rate);

    // from hi-level nterrupt
    void ll_hi_level_triggered_isr_start(int pin_trigger, int trigger_edge);
    void ll_hi_level_triggered_isr_timeout_stop(void);

#ifdef __cplusplus
}
#endif