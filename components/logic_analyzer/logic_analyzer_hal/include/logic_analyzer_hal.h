#pragma once

#include "stdint.h"
#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief logic analyzer callback
     *
     * @param- uint8_t *samle_buf   -  return pointer of samples
     * @param- int samples          - count of samples in 4/8/16 bit word depending of sample width
     * @param- int sample_rate      - real sample rate in HZ
     * @param- int channels         - meashured channels
     * if param == 0 -> timeout detected
     *
     */
    typedef void (*logic_analyzer_cb_t)(uint8_t *samle_buf, int samples, int sample_rate, int channels);

    typedef struct
    {
        int pin[16];                           // GPIO pin ESP32=>(0-39) ESP32S3=>(0-48) , -1 - disable , on 8bit mode use lower 8 pin [0,7]
        int pin_trigger;                       // trigger GPIO pin, -1 - disable
        int trigger_edge;                      // POS_EDGE/NEG_EDGE/ANY_EDGE
        int number_of_samples;                 // Number of samples in 8/16 bit word depending of sample width
        int sample_rate;                       // Sample rate in HZ ( 5000-80000000 ) depending of target, sample width, use psram
        int number_channels;                   // Meashured Channels  8-16 ( 16-esp32, 8/16 esp32s3, 1/2/4 esp32c3)
        int samples_to_psram;                  // Save sample to psram if it`s possible -> 0-ram, 1-psram (esp32s3)
        int meashure_timeout;                  // MAX meashured time in FreeRtos Tick - if timeout = 0 - stop&reset logic analyser
        logic_analyzer_cb_t logic_analyzer_cb; // logic analyzer callback
    } logic_analyzer_config_t;

    /**
     * @brief HW struct returned from logic_analyzer_get_hw_param( channels, psram )
     */
    typedef struct
    {
        int max_channels;     // out - max channels for target
        int min_channels;     // out - min channels for target
        int max_sample_rate;  // out - max sample rate for target & current channels & current psram
        int min_sample_rate;  // out - min sample rate for target & current channels & current psram
        int max_sample_cnt;   // out - max sample cnt for target & psram & free ram/psram
        int min_sample_cnt;   // out - min sample cnt for target & psram
        int available_psram;  // out - 1 psram, 0 ram
        int current_psram;    // in/out hw support psram ( 0/1 ) - return min psram ( ram ) if psram out of range
        int current_channels; // in/out return min channels if channels out of range (8/16)
    } logic_analyzer_hw_param_t;

    /*
     * @breif get current HW logic_analyzer param on dependency of target, free ram, psram, channels
     *
     * @param logic_analyzer_hw_param_t *hw in/out pointer to hw struct
     *                                   current_psram - in psram
     *                                   current_channels - in channels
     *
     * @return
     *     - ESP_OK                 Success
     *     - ESP_ERR_INVALID_ARG    Parameter error
     *     - ESP_FAIL               Initialize fail
     */
    esp_err_t logic_analyzer_get_hw_param(logic_analyzer_hw_param_t *hw);

    /**
     * @brief Start logic analyzer
     *
     * @param config Configurations - see logic_analyzer_config_t struct
     *
     * @return
     *     - ESP_OK                 Success
     *     - ESP_ERR_INVALID_ARG    Parameter error
     *     - ESP_ERR_NO_MEM         No memory to initialize logic_analyzer
     *     - ESP_ERR_INVALID_STATE  logic_analyzer already working
     *     - ESP_FAIL               Initialize fail
     */
    esp_err_t start_logic_analyzer(logic_analyzer_config_t *config);

#ifdef __cplusplus
}
#endif
