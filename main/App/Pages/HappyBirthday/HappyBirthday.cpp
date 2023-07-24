#include "HappyBirthday.h"
#include <cstdio>


#ifdef CONFIG_IDF_TARGET_ESP32S3
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"
    #include "esp_freertos_hooks.h"
    #include "freertos/semphr.h"
    #include "esp_system.h"
    #include "driver/gpio.h"
    #include "driver/uart.h"
    #include "axp173.h"
    #include "esp_err.h"
    #include "esp_log.h"
    #include "driver/gpio.h"
    #include "driver/spi_master.h"
    #include "driver/ledc.h"
    #include "esp_log.h"
    #include "freertos/FreeRTOS.h"
    #include "freertos/task.h"

#define TAG "hpbd"


#define  ZEORO 0
#define  C0 16
#define Db0 17
#define D0  18
#define Eb0 19
#define E0  20
#define F0  21
#define Gb0 23
#define G0  24
#define Ab0 25
#define LA0 27
#define Bb0 29
#define B0  30
#define C1  32
#define Db1 34
#define D1  36
#define Eb1 38
#define E1  41
#define F1  43
#define Gb1 46
#define G1  49
#define Ab1 51
#define LA1 55
#define Bb1 58
#define B1  61
#define C2  65
#define Db2 69
#define D2  73
#define Eb2 77
#define E2  82
#define F2  87
#define Gb2 92
#define G2  98
#define Ab2 103
#define LA2 110
#define Bb2 116
#define B2  123
#define C3  130
#define Db3 138
#define D3  146
#define Eb3 155
#define E3  164
#define F3  174
#define Gb3 185
#define G3  196
#define Ab3 207
#define LA3 220
#define Bb3 233
#define B3  246
#define C4  261
#define Db4 277
#define D4  293
#define Eb4 311
#define E4  329
#define F4  349
#define Gb4 369
#define G4  392
#define Ab4 415
#define LA4 440
#define Bb4 466
#define B4  493
#define C5  523
#define Db5 554
#define D5  587
#define Eb5 622
#define E5  659
#define F5  698
#define Gb5 739
#define G5  783
#define Ab5 830
#define LA5 880
#define Bb5 932
#define B5  987
#define C6  1046
#define Db6 1108
#define D6  1174
#define Eb6 1244
#define E6  1318
#define F6  1396
#define Gb6 1479
#define G6  1567
#define Ab6 1661
#define LA6 1760
#define Bb6 1864
#define B6  1975
#define C7  2093
#define Db7 2217
#define D7  2349
#define Eb7 2489
#define E7  2637
#define F7  2793
#define Gb7 2959
#define G7  3135
#define Ab7 3322
#define LA7 3520
#define Bb7 3729
#define B7  3951
#define C8  4186
#define Db8 4434
#define D8  4698
#define Eb8 4978

// DURATION OF THE NOTES 
#define BPM 160 //  you can change this value changing all the others
// I think tecnically BPM supposed to be 104, but original 120
// from instructable sounds good.  180 sounds speedy, 240 sounds mario, 300 sounds
// middle eastern, 400 middle eastern techno pop?
#define H 2*Q //half 2/4
#define Q 60000/BPM //quarter 1/4 
#define E Q/2   //eighth 1/8
#define S Q/4 // sixteenth 1/16
#define W 4*Q // whole 4/4

typedef struct{
    int freq;
    int dur;
}tone_t;



#endif



using namespace Page;

HappyBirthday::HappyBirthday()
{
}

HappyBirthday::~HappyBirthday()
{
}

void HappyBirthday::onCustomAttrConfig()
{
    
}


#ifdef CONFIG_IDF_TARGET_ESP32S3

// const static tone_t tones[] = {
//     // {1275,2}, {1275,2}, {1014,8}, {1136,8}, {715,8}, {1275,16}, {1700,1}, {1275,2}, {1014,2}, {956,8}, {715,8}, {1136,8}, {1700,16}, {655,1}, {715,2}, {1275,2}, {1700,8}, {956,8}, {715,8}, {1136,8}, {1700,16}
//     {C6, Q}, {C6, Q}, {D6, Q}, {C6, W}, {F6, Q}, {E6, Q},// {ZEORO,  Q/8},
//     {C6, Q}, {C6, Q}, {D6, Q}, {C6, W}, {G6, Q}, {F6, Q}, //{ZEORO, Q/8},
//     {C6, Q}, {C6, Q}, {C7, Q}, {LA6, W}, {F6, Q}, {E6, Q},// {ZEORO, Q/8},
//     {D6, H}, {Bb6, Q}, {Bb6, Q}, {LA6, Q}, {F6, W}, {G6, Q}, {F6, Q}, {ZEORO, Q/8}
// };


// ledc_timer_config_t ledc_timer = {
//           .speed_mode = LEDC_LOW_SPEED_MODE,        // The working mode of the PWM module is high-speed mode
//           .duty_resolution = LEDC_TIMER_10_BIT,     // The resolution of the PWM signal is 10 bits
//           .timer_num = LEDC_TIMER_0,                // The number of the PWM timer is 0
//           .freq_hz = 3000,                          // The frequency of the PWM signal is 1kHz
//           .clk_cfg = LEDC_AUTO_CLK,                 // PWM clock divider is automatically selected
//       };

// ledc_channel_config_t  ledc_channel = {
//           .gpio_num = 46,
//           .speed_mode = LEDC_LOW_SPEED_MODE,
//           .channel = LEDC_CHANNEL_0,  // The number of the PWM channel is 0
//           .intr_type = LEDC_INTR_DISABLE,
//           .timer_sel = LEDC_TIMER_0,  // The number of the PWM timer is 0
//           .duty = 0,                // The duty cycle of the PWM signal is 50%
//           .hpoint = 0,                // The high level duration of the PWM signal is 0
//       };
#endif

void HappyBirthday::onViewLoad()
{
    StatusBar::Appear(false);
    Model.Init();
    View.Create(root);

    // lv_timer_t *timer = lv_timer_create(onTimer, 1000, this);
    // lv_timer_set_repeat_count(timer, 26);

#ifdef CONFIG_IDF_TARGET_ESP32S3
      // gpio_config_t io_conf = {0};
      // io_conf.pin_bit_mask = ((1ULL << 46));
      // io_conf.mode = GPIO_MODE_OUTPUT;
      // io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
      // gpio_config(&io_conf);

      
      // ledc_timer_config(&ledc_timer);

      // // configure PWM channel
      
      // ledc_channel_config(&ledc_channel);

#endif
    // AttachEvent(View.scroll_panel.cont);


}


void HappyBirthday::Buzz_Tone(int freq, int duration)
{
#ifdef CONFIG_IDF_TARGET_ESP32S3

    // if(freq)
    // {
    // ledc_set_freq(ledc_channel.speed_mode, ledc_timer.timer_num, freq);
    // ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, duration);
    // ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    // vTaskDelay(duration / portTICK_PERIOD_MS);

    // ledc_set_duty(ledc_channel.speed_mode, ledc_channel.channel, 0);
    // ledc_update_duty(ledc_channel.speed_mode, ledc_channel.channel);
    // vTaskDelay(5/ portTICK_PERIOD_MS);
    // }
    // else vTaskDelay(duration / portTICK_PERIOD_MS);
#endif
}

void HappyBirthday::onViewDidLoad()
{
}

void HappyBirthday::onViewWillAppear()
{
    lv_obj_set_style_opa(root, LV_OPA_TRANSP, 0);
    lv_obj_fade_in(root, 300, 0);
}

void HappyBirthday::onViewDidAppear()
{
    
}

void HappyBirthday::onViewWillDisappear()
{
    lv_obj_fade_out(root, 300, 0);
}

void HappyBirthday::onViewDidDisappear()
{
}

void HappyBirthday::onViewDidUnload()
{
    View.Delete();
    Model.Deinit();
}

void HappyBirthday::AttachEvent(lv_obj_t *obj)
{
    // lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, LV_EVENT_ALL, this);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    // lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void HappyBirthday::Update()
{
    
}

void HappyBirthday::onTimer(lv_timer_t *timer)
{

     Page::HappyBirthday birthday;
#ifdef CONFIG_IDF_TARGET_ESP32S3
    // ESP_LOGI(TAG, "buzzer update \r\n");

    // for(int i=0; i<sizeof(tones)/sizeof(tone_t); i++)
    //     {
    //         birthday.Buzz_Tone(tones[i].freq, tones[i].dur);
    //     }
    // vTaskDelay(100/ portTICK_PERIOD_MS);

#endif
}




void HappyBirthday::onEvent(lv_event_t *event)
{

    // HappyBirthday *instance = (HappyBirthday *)lv_event_get_user_data(event);
    // LV_ASSERT_NULL(instance);


    // lv_obj_t *obj = lv_event_get_current_target(event);
    // lv_event_code_t code = lv_event_get_code(event);



}
