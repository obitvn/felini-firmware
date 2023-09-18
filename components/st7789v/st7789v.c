#include "st7789v.h"

#include <stdlib.h>
#include <string.h>

#include "driver/gpio.h"
#include "driver/spi_master.h"
#include "driver/ledc.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define ST7789V_PIN_SCL (12)
#define ST7789V_PIN_SDA (11)
#define ST7789V_PIN_RES (13)
#define ST7789V_PIN_DC (14)
#define ST7789V_PIN_CS (10)
#define ST7789V_PIN_BLK (17)

#define CONFIG_ST7789V_ORIENTATION_0 1

#if defined(CONFIG_ST7789V_USE_COUSTOM_SPI_SPEED)
#define ST7789V_SPI_SPEED_MHZ (80 * 1000 * 1000)
#else
#if CONFIG_ST7789V_SPI_SPEED_8MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_8M)
#elif CONFIG_ST7789V_SPI_SPEED_9MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_9M)
#elif CONFIG_ST7789V_SPI_SPEED_10MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_10M)
#elif CONFIG_ST7789V_SPI_SPEED_13MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_13M)
#elif CONFIG_ST7789V_SPI_SPEED_16MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_16M)
#elif CONFIG_ST7789V_SPI_SPEED_20MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_20M)
#elif CONFIG_ST7789V_SPI_SPEED_26MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_26M)
#elif CONFIG_ST7789V_SPI_SPEED_40MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_40M)
#elif CONFIG_ST7789V_SPI_SPEED_80MHZ
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_80M)
#else
#define ST7789V_SPI_SPEED_MHZ (SPI_MASTER_FREQ_40M)
#endif
#endif

#define ST7789V_SPI_HOST (SPI2_HOST)
#define ORIENTATION (CONFIG_ST7789V_ORIENTATION_0)

#define MAX_TRANSFER_SIZE (32768)

/*The LCD needs a bunch of command/argument values to be initialized. They are
 * stored in this struct. */
typedef struct {
  uint8_t cmd;
  uint8_t data[16];
  uint8_t databytes;  // No of data in data; bit 7 = delay after set; 0xFF = end
                      // of cmds.
} lcd_init_cmd_t;

static const char *TAG = "ST7789V";

static spi_device_handle_t spi;
static bool s_is_st7789v_inited = false;

void st7789v_fill_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

static void st7789v_send_cmd(uint8_t cmd) {
  esp_err_t ret;
  spi_transaction_t t;
  memset(&t, 0, sizeof(t));
  t.length = 8;
  t.tx_buffer = &cmd;
  t.user = (void *)0;
  ret = spi_device_polling_transmit(spi, &t);
  assert(ret == ESP_OK);
}


static void st7789v_send_addr(uint16_t addr1, uint16_t addr2) {
  static uint8_t addr_data[4];
  addr_data[0] = (addr1 >> 8) & 0xFF;
  addr_data[1] = addr1 & 0xFF;
  addr_data[2] = (addr2 >> 8) & 0xFF;
  addr_data[3] = addr2 & 0xFF;

  esp_err_t ret;
  spi_transaction_t t;
  memset(&t, 0, sizeof(t));
  t.length = 32;
  t.tx_buffer = &addr_data;
  t.user = (void *)1;        // D/C needs to be set to 1
  ret = spi_device_polling_transmit(spi, &t);
  assert(ret == ESP_OK);
}


static void st7789v_send_color( uint16_t color, uint16_t size) {
  static uint8_t color_data[1024];
  int index = 0;
  for(int i=0;i<size;i++) {
    color_data[index++] = (color >> 8) & 0xFF;
    color_data[index++] = color & 0xFF;
  }

  esp_err_t ret;
  spi_transaction_t t;
  memset(&t, 0, sizeof(t));
  t.length = size*2*8;
  t.tx_buffer = &color_data;
  t.user = (void *)1;        // D/C needs to be set to 1
  ret = spi_device_polling_transmit(spi, &t);
  assert(ret == ESP_OK);
}



static void st7789v_send_data(uint8_t *data, uint16_t length) {
  esp_err_t ret;
  spi_transaction_t t;
  if (length == 0) return;   // no need to send anything
  memset(&t, 0, sizeof(t));  // Zero out the transaction
  t.length = length * 8;     // Len is in bytes, transaction length is in bits.
  t.tx_buffer = data;        // Data
  t.user = (void *)1;        // D/C needs to be set to 1
  ret = spi_device_polling_transmit(spi, &t);  // Transmit!
  assert(ret == ESP_OK);
}

static void st7789v_set_orientation(uint8_t orientation) {
  const char *orientation_str[] = {"PORTRAIT", "PORTRAIT_INVERTED", "LANDSCAPE",
                                   "LANDSCAPE_INVERTED"};
  ESP_LOGI(TAG, "Display orientation: %s", orientation_str[orientation]);
  uint8_t data[] = {0x00, 0x60, 0xC0, 0xA0};
  ESP_LOGI(TAG, "0x36 command value: 0x%02X", data[orientation]);
  st7789v_send_cmd(ST7789V_MADCTL);
  st7789v_send_data(&data[orientation], 1);
}

static void spi_pre_transfer_callback(spi_transaction_t *t) {
  int dc = (int)t->user;
  gpio_set_level(ST7789V_PIN_DC, dc);
}

static void st7789v_gpio_init(void) {
  esp_err_t ret;
  spi_bus_config_t buscfg = {.miso_io_num = -1,
                             .mosi_io_num = ST7789V_PIN_SDA,
                             .sclk_io_num = ST7789V_PIN_SCL,
                             .quadwp_io_num = -1,
                             .quadhd_io_num = -1,
                             .max_transfer_sz = MAX_TRANSFER_SIZE};

  spi_device_interface_config_t devcfg = {
      .clock_speed_hz = ST7789V_SPI_SPEED_MHZ,
      .mode = 0,
      .spics_io_num = ST7789V_PIN_CS,
      .queue_size = 17,
      .pre_cb = spi_pre_transfer_callback,
  };

  ret = spi_bus_initialize(ST7789V_SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);
  ESP_ERROR_CHECK(ret);
  ret = spi_bus_add_device(ST7789V_SPI_HOST, &devcfg, &spi);
  ESP_ERROR_CHECK(ret);

  gpio_config_t io_conf = {0};
  io_conf.pin_bit_mask = ((1ULL << ST7789V_PIN_DC) | (1ULL << ST7789V_PIN_RES) |
                          (1ULL << ST7789V_PIN_BLK));
  io_conf.mode = GPIO_MODE_OUTPUT;
  io_conf.pull_up_en = true;
  gpio_config(&io_conf);

  gpio_set_direction(ST7789V_PIN_RES, GPIO_MODE_OUTPUT);
  gpio_set_pull_mode(ST7789V_PIN_RES, GPIO_PULLUP_ONLY);

  ledc_timer_config_t timer_conf = {
      .duty_resolution = LEDC_TIMER_10_BIT, // The resolution of the PWM signal is 10 bits
      .freq_hz = 2000,                      // The frequency of the PWM signal is 1kHz
      .speed_mode = LEDC_LOW_SPEED_MODE,    // The working mode of the PWM module is high-speed mode
      .timer_num = LEDC_TIMER_0,            // The number of the PWM timer is 0
      .clk_cfg = LEDC_AUTO_CLK,             // PWM clock divider is automatically selected
  };
  ledc_timer_config(&timer_conf);

  // Configure PWM channels
  ledc_channel_config_t ch_conf = {
      .gpio_num = ST7789V_PIN_BLK,
      .speed_mode = LEDC_LOW_SPEED_MODE,
      .channel = LEDC_CHANNEL_0, // The number of PWM channel is 0
      .timer_sel = LEDC_TIMER_0, // The number of the PWM timer is 0
      .duty = 0,                 // The duty cycle of the PWM signal is 50%
      .hpoint = 0,               // The high level duration of the PWM signal is 0
  };
  ledc_channel_config(&ch_conf);
}



static void st7789v_clear_screen();

void st7789v_init(void) {
  if (s_is_st7789v_inited) {
    ESP_LOGW(TAG, "ST7789V already initialized.");
  } else {
    s_is_st7789v_inited = true;
  }
  st7789v_gpio_init();

  lcd_init_cmd_t st7789v_init_cmds[] = {
      {0x11, {0}, 0x08},

      {0x3A, {0x05}, 1},
      {0xC5, {0x1A}, 1},
      {0x36, {0x00}, 1},

      {0xB2, {0x05, 0x05, 0x00, 0x33, 0x33}, 5},
      {0xB7, {0x05}, 1},

      {0xBB, {0x3F}, 1},
      {0xC0, {0x2C}, 1},
      {0xC2, {0x01}, 1},
      {0xC3, {0x0F}, 1},
      {0xC4, {0x20}, 1},
      {0xC6, {0X01}, 1}, // Set to 0x28 if your display is flipped
      {0x35, {0x01}, 1}, // tearing_effect_on
      {0xD0, {0xa4, 0xa1}, 2},

      {0xE8, {0x03}, 1},
      {0xE9, {0x09, 0x09, 0x08}, 3},

      {0xE0,
       {0xD0, 0x05, 0x09, 0x09, 0x08, 0x14, 0x28, 0x33, 0x3F, 0x07, 0x13, 0x14,
        0x28, 0x30},
       14},
      {0xE1,
       {0xD0, 0x05, 0x09, 0x09, 0x08, 0x03, 0x24, 0x32, 0x32, 0x3B, 0x14, 0x13,
        0x28, 0x2F},
       14},
      {0x2A, {0x00, 0x00, 0x01, 0x18}, 4}, // width
      {0x2B, {0x00, 000, 0x00, 0xF0}, 4},  // high

      {0x21, {0}, 0},
      {0x29, {0}, 0},

      {0, {0}, 0xff},
  };

  ESP_LOGI(TAG, "ST7789 initialization starts.");
  st7789v_fill_rect(0,0,320,320, 0);//clear screen
  gpio_set_level(ST7789V_PIN_RES, 0);
  vTaskDelay(pdMS_TO_TICKS(150));
  gpio_set_level(ST7789V_PIN_RES, 1);
  vTaskDelay(pdMS_TO_TICKS(100));
  st7789v_fill_rect(0,0,320,320, 0);//clear screen


  uint16_t cmd = 0;
  while (st7789v_init_cmds[cmd].databytes != 0xff) {
    st7789v_send_cmd(st7789v_init_cmds[cmd].cmd);
    st7789v_send_data(st7789v_init_cmds[cmd].data,
                      st7789v_init_cmds[cmd].databytes & 0x1F);
    if (st7789v_init_cmds[cmd].databytes & 0x80) {
      vTaskDelay(pdMS_TO_TICKS(100));
    }
    cmd++;
  }
  st7789v_set_orientation(ORIENTATION);
  st7789v_fill_rect(0,0,320,320, 0);//clear screen
  vTaskDelay(pdMS_TO_TICKS(100));
  st7789v_fill_rect(0,0,320,320, 0);//clear screen
  st7789v_backlight_set(500); // 50%
}
void st7789v_backlight_set(uint16_t brightness) {
  if (brightness > 2000) {
    brightness = 2000;
  }
  ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, brightness);
  ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
}

static uint8_t sByte[700];


void st7789v_flush(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2,
                   void *color_map) {
  static uint32_t transfer_num = 0;
  spi_transaction_t *rtrans;

#if defined(CONFIG_ST7789V_ORIENTATION_0) || \
    defined(CONFIG_ST7789V_ORIENTATION_180)
  x1 += 20;
  x2 += 20;
#else
  x1 += 20;
  x2 += 20;
#endif

  uint32_t chunk_lines = MAX_TRANSFER_SIZE / ((x2 - x1 + 1) * 2);
  uint32_t size_per_chunk = (x2 - x1 + 1) * chunk_lines * 2;
  uint32_t chunk_num = (y2 - y1 + 1) / chunk_lines;
  uint32_t remain_lines = (y2 - y1 + 1) % chunk_lines;
  uint32_t chunk_total = chunk_num + (remain_lines > 0 ? 1 : 0);


  static spi_transaction_t trans[6][6] = {0};

  for (int i = 0; i < chunk_total; i++) {
    for (int x = 0; x < 6; x++) {
      memset(&trans[i][x], 0, sizeof(spi_transaction_t));
      if ((x & 1) == 0) {
        // Even transfers are commands
        trans[i][x].length = 8;
        trans[i][x].user = (void *)0;
      } else {
        // Odd transfers are data
        trans[i][x].length = 8 * 4;
        trans[i][x].user = (void *)1;
      }
      trans[i][x].flags = SPI_TRANS_USE_TXDATA;
    }
  }

  uint8_t *color_map_ptr = (uint8_t *)color_map;
  uint32_t data_offset = 0;
  // Split the data, each transmission is up to MAX_TRANSFER_SIZE
  for (int i = 0; i < chunk_total; i++) {
    if (i < chunk_num) {
      trans[i][0].tx_data[0] = ST7789V_CASET;     //Column Address Set
      trans[i][1].tx_data[0] = (x1 >> 8) & 0xFF;  // Start Col High
      trans[i][1].tx_data[1] = (x1)&0xFF;         // Start Col Low
      trans[i][1].tx_data[2] = (x2 >> 8) & 0xFF;  // End Col High
      trans[i][1].tx_data[3] = (x2)&0xFF;         // End Col Low
      trans[i][2].tx_data[0] = ST7789V_RASET;     // Page address set
      trans[i][3].tx_data[0] = ((y1 + i * chunk_lines) >> 8) & 0xFF;
      trans[i][3].tx_data[1] = (y1 + i * chunk_lines) & 0xFF;  // start page low
      trans[i][3].tx_data[2] = ((y1 + (i + 1) * chunk_lines - 1) >> 8) & 0xFF;
      trans[i][3].tx_data[3] = (y1 + (i + 1) * chunk_lines - 1) & 0xFF;
      trans[i][4].tx_data[0] = ST7789V_RAMWR;  // memory write

      trans[i][5].tx_buffer = (void *)(color_map_ptr + data_offset);
      trans[i][5].length = size_per_chunk * 8;
      trans[i][5].flags = 0;

      data_offset += size_per_chunk;
    } else {
      trans[i][0].tx_data[0] = ST7789V_CASET;
      trans[i][1].tx_data[0] = (x1 >> 8) & 0xFF;  // Start Col High
      trans[i][1].tx_data[1] = (x1)&0xFF;         // Start Col Low
      trans[i][1].tx_data[2] = (x2 >> 8) & 0xFF;  // End Col High
      trans[i][1].tx_data[3] = (x2)&0xFF;         // End Col Low
      trans[i][2].tx_data[0] = ST7789V_RASET;     // Page address set
      trans[i][3].tx_data[0] = ((y1 + i * chunk_lines) >> 8) & 0xFF;
      trans[i][3].tx_data[1] = (y1 + i * chunk_lines) & 0xFF;  // start page low
      trans[i][3].tx_data[2] = (y2 >> 8) & 0xFF;
      trans[i][3].tx_data[3] = (y2)&0xFF;
      trans[i][4].tx_data[0] = ST7789V_RAMWR;  // memory write

      trans[i][5].tx_buffer = (void *)(color_map_ptr + data_offset);
      trans[i][5].length = remain_lines * (x2 - x1) * 2 * 8;
      trans[i][5].flags = 0;
    }
  }
  // Queue all transactions.
  for (int i = 0; i < chunk_total; i++) {
    for (int x = 0; x < 6; x++) {
      esp_err_t ret = spi_device_transmit(spi, &trans[i][x]);
      assert(ret == ESP_OK);
      // ESP_LOGW(TAG, "+");
      transfer_num++;
    }
  }

  //When we are here, the SPI driver is busy (in the background) getting the transactions sent. That happens
    //mostly using DMA, so the CPU doesn't have much to do here. We're not going to wait for the transaction to
    //finish because we may as well spend the time calculating the next line. When that is done, we can call
    //send_line_finish, which will wait for the transfers to be done and check their status.
}




// Draw rectangle of filling
// x1:Start X coordinate
// y1:Start Y coordinate
// x2:End X coordinate
// y2:End Y coordinate
// color:color
void st7789v_fill_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
  if (x1 >= 320) return;
  if (x2 >= 320) x2=320-1;
  if (y1 >= 320) return;
  if (y2 >= 320) y2=320-1;

  uint16_t _x1 = x1 + 20;
  uint16_t _x2 = x2 + 20;
  uint16_t _y1 = y1 + 20;
  uint16_t _y2 = y2 + 20;

  st7789v_send_cmd(0x2A);  // set column(x) address
  st7789v_send_addr(_x1, _x2);
  st7789v_send_cmd(0x2B);  // set Page(y) address
  st7789v_send_addr(_y1, _y2);
  st7789v_send_cmd(0x2C);  //  Memory Write
  for(int i=_x1;i<=_x2;i++){
    uint16_t size = _y2-_y1+1;
    st7789v_send_color(color, size);
  }
}