/**
 * @file st7789.c
 *
 * Mostly taken from lbthomsen/esp-idf-littlevgl github.
 */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

#include "esp_log.h"

#include "st7789.h"

#include "disp_spi.h"
#include "driver/gpio.h"

/*********************
 *      DEFINES
 *********************/
#define TAG "st7789"
/**********************
 *      TYPEDEFS
 **********************/

/*The LCD needs a bunch of command/argument values to be initialized. They are stored in this struct. */
typedef struct {
    uint8_t cmd;
    uint8_t databytes; //No of data in data; bit 7 = delay after set; 0xFF = end of cmds.
    uint8_t data[16];
    
} lcd_init_cmd_t;

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void st7789_set_orientation(uint8_t orientation);

static void st7789_send_color(void *data, size_t length);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
void st7789_init(void)
{
    lcd_init_cmd_t st7789_init_cmds[] = {

//         //COLMOD (3Ah): Interface Pixel Format
//         {0x3A, {0x55}, 1}, //‘0101’ = 65K of RGB interface, ‘0101’ = 16bit/pixel
//         {0, {0}, 0x80}, //delay 100ms
//         {0x36, {0x00}, 1}, ////Memory Data Access Control
//         {ST7789_GAMSET, {0x01}, 1},
//         {ST7789_PVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x31, 0x54, 0x47, 0x0E, 0x1C, 0x17, 0x1B, 0x1E}, 14},
//         {ST7789_NVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x31, 0x54, 0x47, 0x0E, 0x1C, 0x17, 0x1B, 0x1E}, 14},
//         {0xB2, {0x0c, 0x0c, 0x00, 0x33, 0x33}, 5}, //Row Address Set
//         {0x2A, {0x00, 0x00, 0x00, 0xF0}, 4}, //Column Address Set
//         {0x2B, {0x00, 0x00, 0x00, 0xF0}, 4}, //Row Address Set
// #if ST7789_INVERT_COLORS == 1
//         {ST7789_INVON, {0}, 0}, // set inverted mode
// #else
//         {ST7789_INVOFF, {0}, 0}, // set non-inverted mode
// #endif
//         {0, {0}, 0x80}, //delay 100ms
//         {0x13, {0}, 0}, //Normal Display Mode On
//         {0, {0}, 0x80}, //delay 100ms
//         {0x29, {0}, 0}, //Display ON
//         {0, {0}, 0x80}, //delay 100ms
//         {0, {0}, 0xff},

//         {0xCF, {0x00, 0x83, 0X30}, 3},
//         {0, {0}, 0x80}, //delay 100ms
//         {0, {0}, 0x80}, //delay 100ms
//         {0xED, {0x64, 0x03, 0X12, 0X81}, 4},
//         {ST7789_PWCTRL2, {0x85, 0x01, 0x79}, 3},
//         {0xCB, {0x39, 0x2C, 0x00, 0x34, 0x02}, 5},
//         {0xF7, {0x20}, 1},
//         {0xEA, {0x00, 0x00}, 2},
//         {ST7789_LCMCTRL, {0x26}, 1},
//         {ST7789_IDSET, {0x11}, 1},
//         {ST7789_VCMOFSET, {0x35, 0x3E}, 2},
//         {ST7789_CABCCTRL, {0xBE}, 1},
//         {ST7789_MADCTL, {0x00}, 1}, // Set to 0x28 if your display is flipped
//         {ST7789_COLMOD, {0x55}, 1},
//         {0, {0}, 0x80}, //delay 100ms
//         {0, {0}, 0x80}, //delay 100ms

// #if ST7789_INVERT_COLORS == 1
//         {ST7789_INVON, {0}, 0}, // set inverted mode
// #else
//         {ST7789_INVOFF, {0}, 0}, // set non-inverted mode
// #endif
//         {0, {0}, 0x80}, //delay 100ms
//         {0, {0}, 0x80}, //delay 100ms
//         {ST7789_RGBCTRL, {0x00, 0x1B}, 2},
//         {0xF2, {0x08}, 1},
//         {ST7789_GAMSET, {0x01}, 1},
//         {ST7789_PVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x32, 0x44, 0x42, 0x06, 0x0E, 0x12, 0x14, 0x17}, 14},
//         {ST7789_NVGAMCTRL, {0xD0, 0x00, 0x02, 0x07, 0x0A, 0x28, 0x31, 0x54, 0x47, 0x0E, 0x1C, 0x17, 0x1B, 0x1E}, 14},
//         {ST7789_CASET, {0x00, 0x00, 0x00, 0xEF}, 4},
//         {ST7789_RASET, {0x00, 0x00, 0x01, 0x3f}, 4},
//         {ST7789_RAMWR, {0}, 0},
//         {ST7789_GCTRL, {0x07}, 1},
//         {0xB6, {0x0A, 0x82, 0x27, 0x00}, 4},
//         {ST7789_SLPOUT, {0}, 0x80},
//         {0, {0}, 0x80}, //delay 100ms
//         {0, {0}, 0x80}, //delay 100ms
//         {ST7789_DISPON, {0}, 0x80},
//         {0, {0}, 0x80}, //delay 100ms
//         {0, {0}, 0xff},
        {0x11, 0, {0x00}},

    #if CONFIG_LV_DISPLAY_ORIENTATION==0
        {0x36, 1, {0x00}},
    #elif CONFIG_LV_DISPLAY_ORIENTATION==1
        {0x36, 1, {0xC0}},
    #elif CONFIG_LV_DISPLAY_ORIENTATION==2
        {0x36, 1, {0x70}},
    #else
        {0x36, 1, {0xA0}},
    #endif

        {0x3A, 1, {0x55}},
        {0xB2, 7, {0x0c, 0x0c, 0x00, 0x33, 0x33, 0xb7, 0x75}},
        {0xC2, 1, {0x01}},
        {0xC3, 1, {0x16}},
        {0xC4, 1, {0x20}},
        {0xC6, 1, {0x0F}},
        {0xD0, 2, {0xA4, 0xA1}},
        {0xD6, 1, {0xA1}},
        {0xBB, 1, {0x3B}},
        {0xE0, 4, {0xf0, 0x0b, 0x11, 0x0e, 0x0d, 0x19, 0x36, 0x33, 0x4b, 0x07, 0x14, 0x14, 0x2c, 0x2e}},
        {0xE1, 4, {0xf0, 0x0d, 0x12, 0x0b, 0x09, 0x03, 0x32, 0x44, 0x48, 0x39, 0x16, 0x16, 0x2d, 0x30}},
        {0x2A, 4, {0x00, 0x00, 0x00, 239}}, //宽度
        {0x2B, 4, {0x00, 000, 0x00, 239}},  //高度
        {0x21, 0, {0x00}},
        {0x29, 0, {0x00}},
        {0x2C, 0, {0x00}},
    };

    //Initialize non-SPI GPIOs
    esp_rom_gpio_pad_select_gpio(ST7789_DC);
    gpio_set_direction(ST7789_DC, GPIO_MODE_OUTPUT);

#if !defined(ST7789_SOFT_RST)
    esp_rom_gpio_pad_select_gpio(ST7789_RST);
    gpio_set_direction(ST7789_RST, GPIO_MODE_OUTPUT);
#endif

    //Reset the display
#if !defined(ST7789_SOFT_RST)
    gpio_set_level(ST7789_RST, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(ST7789_RST, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
#else
    st7789_send_cmd(ST7789_SWRESET);
#endif
    st7789_draw(0,0, 240, 320, 0); //CLEAR SCREEN
    printf("ST7789 initialization.\n");

    st7789_send_cmd(ST7789_SLPOUT);
    vTaskDelay(255 / portTICK_PERIOD_MS);
    // st7789_send_cmd(ST7789_NORON);

    //display and color format setting//
    //Send all the commands

    uint16_t cmd = 0;
    while (st7789_init_cmds[cmd].databytes!=0xff) {
        st7789_send_cmd(st7789_init_cmds[cmd].cmd);
        st7789_send_data(st7789_init_cmds[cmd].data, st7789_init_cmds[cmd].databytes&0x1F);
        if (st7789_init_cmds[cmd].databytes & 0x80) {
                vTaskDelay(100 / portTICK_PERIOD_MS);
        }
        cmd++;
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);
    st7789_draw(0,0, 240, 320, 0); //CLEAR SCREEN


    // st7789_set_orientation(CONFIG_LV_DISPLAY_ORIENTATION);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    
}

/* The ST7789 display controller can drive up to 320*240 displays, when using a 240*240 or 240*135
 * displays there's a gap of 80px or 40/52/53px respectively. 52px or 53x offset depends on display orientation.
 * We need to edit the coordinates to take into account those gaps, this is not necessary in all orientations. */
void st7789_flush(lv_disp_drv_t * drv, const lv_area_t * area, lv_color_t * color_map)
{
    uint8_t data[4] = {0};

    uint16_t offsetx1 = area->x1;
    uint16_t offsetx2 = area->x2;
    uint16_t offsety1 = area->y1;
    uint16_t offsety2 = area->y2;

#if (CONFIG_LV_TFT_DISPLAY_OFFSETS)
    offsetx1 += CONFIG_LV_TFT_DISPLAY_X_OFFSET;
    offsetx2 += CONFIG_LV_TFT_DISPLAY_X_OFFSET;
    offsety1 += CONFIG_LV_TFT_DISPLAY_Y_OFFSET;
    offsety2 += CONFIG_LV_TFT_DISPLAY_Y_OFFSET;

#elif (LV_HOR_RES_MAX == 240) && (LV_VER_RES_MAX == 240)
    #if (CONFIG_LV_DISPLAY_ORIENTATION_PORTRAIT)
        offsetx1 += 80;
        offsetx2 += 80;
    #elif (CONFIG_LV_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED)
        offsety1 += 80;
        offsety2 += 80;
    #endif
#elif (LV_HOR_RES_MAX == 280) && (LV_VER_RES_MAX == 240)
    #if (CONFIG_LV_DISPLAY_ORIENTATION_PORTRAIT)
        offsetx1 += 20;
        offsetx2 += 20;
    #elif (CONFIG_LV_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED)
        offsety1 += 0;
        offsety2 += 0;
    #endif
#elif (LV_HOR_RES_MAX == 240) && (LV_VER_RES_MAX == 135)
    #if (CONFIG_LV_DISPLAY_ORIENTATION_PORTRAIT) || \
        (CONFIG_LV_DISPLAY_ORIENTATION_PORTRAIT_INVERTED)
        offsetx1 += 40;
        offsetx2 += 40;
        offsety1 += 53;
        offsety2 += 53;
    #endif
#elif (LV_HOR_RES_MAX == 135) && (LV_VER_RES_MAX == 240)
    #if (CONFIG_LV_DISPLAY_ORIENTATION_LANDSCAPE) || \
        (CONFIG_LV_DISPLAY_ORIENTATION_LANDSCAPE_INVERTED)
        offsetx1 += 52;
        offsetx2 += 52;
        offsety1 += 40;
        offsety2 += 40;
    #endif
#endif

    /*Column addresses*/
    st7789_send_cmd(ST7789_CASET);
    data[0] = (offsetx1 >> 8) & 0xFF;
    data[1] = offsetx1 & 0xFF;
    data[2] = (offsetx2 >> 8) & 0xFF;
    data[3] = offsetx2 & 0xFF;
    st7789_send_data(data, 4);

    /*Page addresses*/
    st7789_send_cmd(ST7789_RASET);
    data[0] = (offsety1 >> 8) & 0xFF;
    data[1] = offsety1 & 0xFF;
    data[2] = (offsety2 >> 8) & 0xFF;
    data[3] = offsety2 & 0xFF;
    st7789_send_data(data, 4);

    /*Memory write*/
    st7789_send_cmd(ST7789_RAMWR);

    size_t size = (size_t)lv_area_get_width(area) * (size_t)lv_area_get_height(area);

    st7789_send_color((void*)color_map, size * 2);

}

/**********************
 *   STATIC FUNCTIONS
 **********************/
void st7789_send_cmd(uint8_t cmd)
{
    disp_wait_for_pending_transactions();
    gpio_set_level(ST7789_DC, 0);
    disp_spi_send_data(&cmd, 1);
}

void st7789_send_data(void * data, uint16_t length)
{
    disp_wait_for_pending_transactions();
    gpio_set_level(ST7789_DC, 1);
    disp_spi_send_data(data, length);
}

static void st7789_send_color(void * data, size_t length)
{
    disp_wait_for_pending_transactions();
    gpio_set_level(ST7789_DC, 1);
    disp_spi_send_colors(data, length);
}

static void st7789_set_orientation(uint8_t orientation)
{
    // ESP_ASSERT(orientation < 4);

    const char *orientation_str[] = {
        "PORTRAIT", "PORTRAIT_INVERTED", "LANDSCAPE", "LANDSCAPE_INVERTED"
    };

    ESP_LOGI(TAG, "Display orientation: %s", orientation_str[orientation]);

    uint8_t data[] =
    {
#if CONFIG_LV_PREDEFINED_DISPLAY_TTGO
	0x60, 0xA0, 0x00, 0xC0
#else
	0xC0, 0x00, 0x60, 0xA0
#endif
    };

    ESP_LOGI(TAG, "0x36 command value: 0x%02X", data[orientation]);

    st7789_send_cmd(ST7789_MADCTL);
    st7789_send_data((void *) &data[orientation], 1);
}

static uint8_t sByte[1024];

void st7789_draw(uint16_t offsetx1, uint16_t offsety1, uint16_t w, uint16_t h, uint16_t color)
{

    uint8_t data[4] = {0};
    uint16_t offsetx2;
     uint16_t offsety2;

    offsetx2 = offsetx1 + w-1;
    offsety2 = offsety1 + h-1;

    /*Column addresses*/
    st7789_send_cmd(ST7789_CASET);
    data[0] = (offsetx1 >> 8) & 0xFF;
    data[1] = offsetx1 & 0xFF;
    data[2] = (offsetx2 >> 8) & 0xFF;
    data[3] = offsetx2 & 0xFF;
    st7789_send_data(data, 4);

    /*Page addresses*/
    st7789_send_cmd(ST7789_RASET);
    data[0] = (offsety1 >> 8) & 0xFF;
    data[1] = offsety1 & 0xFF;
    data[2] = (offsety2 >> 8) & 0xFF;
    data[3] = offsety2 & 0xFF;
    st7789_send_data(data, 4);

    /*Memory write*/
    st7789_send_cmd(ST7789_RAMWR);



    for(int i=offsetx1; i<=offsetx2; i++)
    {
        uint16_t size = offsety2-offsety1+1;

        
        int index = 0;
        for(int i=0;i<size;i++) {
            sByte[index++] = (color >> 8) & 0xFF;
            sByte[index++] = color & 0xFF;
        }

        disp_wait_for_pending_transactions();
        gpio_set_level(ST7789_DC, 1);
        disp_spi_send_data(sByte, size*2);
    }
}