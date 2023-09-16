


#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "usbd_core.h"
#include "usbd_cdc.h"
#include "usbd_msc.h"
#include "usb_jtag_serial_esp32s3.h"
#include "logic_analyzer_cdc.h"

#include "ringbuffer.h"

ring_buffer_t cdc_write_ring_buffer;
ring_buffer_t cdc_read_ring_buffer;

/*!< endpoint address */
#define CDC_IN_EP 0x81
#define CDC_OUT_EP 0x04
#define CDC_INT_EP 0x83

#define MSC_IN_EP 0x84
#define MSC_OUT_EP 0x05

#define USBD_VID 0xFFFF
#define USBD_PID 0xFFFF
#define USBD_MAX_POWER 100
#define USBD_LANGID_STRING 1033

/*!< config descriptor size */
#define USB_CONFIG_SIZE (9 + CDC_ACM_DESCRIPTOR_LEN + MSC_DESCRIPTOR_LEN)

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

/*!< global descriptor */
static const uint8_t cdc_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x03, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    CDC_ACM_DESCRIPTOR_INIT(0x00, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, 0x02),
    MSC_DESCRIPTOR_INIT(0x02, MSC_OUT_EP, MSC_IN_EP, 0x00),
    ///////////////////////////////////////
    /// string0 descriptor
    ///////////////////////////////////////
    USB_LANGID_INIT(USBD_LANGID_STRING),
    ///////////////////////////////////////
    /// string1 descriptor
    ///////////////////////////////////////
    0x14,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ///////////////////////////////////////
    /// string2 descriptor
    ///////////////////////////////////////
    0x26,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'C', 0x00,                  /* wcChar0 */
    'h', 0x00,                  /* wcChar1 */
    'e', 0x00,                  /* wcChar2 */
    'r', 0x00,                  /* wcChar3 */
    'r', 0x00,                  /* wcChar4 */
    'y', 0x00,                  /* wcChar5 */
    'U', 0x00,                  /* wcChar6 */
    'S', 0x00,                  /* wcChar7 */
    'B', 0x00,                  /* wcChar8 */
    ' ', 0x00,                  /* wcChar9 */
    'C', 0x00,                  /* wcChar10 */
    '-', 0x00,                  /* wcChar11 */
    'M', 0x00,                  /* wcChar12 */
    ' ', 0x00,                  /* wcChar13 */
    'D', 0x00,                  /* wcChar14 */
    'E', 0x00,                  /* wcChar15 */
    'M', 0x00,                  /* wcChar16 */
    'O', 0x00,                  /* wcChar17 */
    ///////////////////////////////////////
    /// string3 descriptor
    ///////////////////////////////////////
    0x16,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    '2', 0x00,                  /* wcChar0 */
    '0', 0x00,                  /* wcChar1 */
    '2', 0x00,                  /* wcChar2 */
    '2', 0x00,                  /* wcChar3 */
    '1', 0x00,                  /* wcChar4 */
    '2', 0x00,                  /* wcChar5 */
    '3', 0x00,                  /* wcChar6 */
    '4', 0x00,                  /* wcChar7 */
    '5', 0x00,                  /* wcChar8 */
    '6', 0x00,                  /* wcChar9 */
#ifdef CONFIG_USB_HS
    ///////////////////////////////////////
    /// device qualifier descriptor
    ///////////////////////////////////////
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x00,
    0x02,
    0x02,
    0x02,
    0x01,
    0x40,
    0x01,
    0x00,
#endif
    0x00
};

static char *TAG = "device_cdc_main";
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t read_buffer[2048];
USB_NOCACHE_RAM_SECTION USB_MEM_ALIGNX uint8_t write_buffer[2048];
static int write_buffer_len = 0;

volatile bool la_ep_tx_busy_flag = false;



static void la_usbd_cdc_acm_bulk_out(uint8_t ep, uint32_t nbytes)
{
    // printf("actual out len:%ld\r\n", nbytes);
    ring_buffer_queue_arr(&cdc_read_ring_buffer, (char *)read_buffer, nbytes);
    /* setup first out ep read transfer */
    usbd_ep_start_read(CDC_OUT_EP, read_buffer, sizeof(read_buffer));
}

static void la_usbd_cdc_acm_bulk_in(uint8_t ep, uint32_t nbytes)
{
    // printf("actual in len:%ld\r\n", nbytes);
    if ((nbytes % CDC_MAX_MPS) == 0 && nbytes)
    {
        usbd_ep_start_write(CDC_IN_EP, NULL, 0);
    }
    else
    {
        la_ep_tx_busy_flag = false;
    }
}

struct usbd_endpoint la_cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = la_usbd_cdc_acm_bulk_out};

struct usbd_endpoint la_cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = la_usbd_cdc_acm_bulk_in};

struct usbd_interface la_intf0;
struct usbd_interface la_intf1;
struct usbd_interface la_intf2;
extern struct usb_msosv1_descriptor la_msosv1_desc;

static void cdc_acm_init(void)
{
    const uint8_t data[10] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x30};

    memcpy(&write_buffer[0], data, 10);

    usbd_desc_register(cdc_descriptor);
    
    usbd_add_endpoint(&la_cdc_out_ep);
    usbd_add_endpoint(&la_cdc_in_ep);
    usbd_add_interface(usbd_cdc_acm_init_intf(&la_intf0));
    usbd_add_interface(usbd_cdc_acm_init_intf(&la_intf1));
    usbd_add_interface(usbd_msc_init_intf(&la_intf2, MSC_OUT_EP, MSC_IN_EP));

    usbd_initialize();

    while (!usb_device_is_configured())
    {
        printf(".");
        vTaskDelay(100);
    }
}

// void usbd_cdc_acm_set_line_coding(uint8_t intf, struct cdc_line_coding *line_coding)
// {
// }

// void usbd_cdc_acm_get_line_coding(uint8_t intf, struct cdc_line_coding *line_coding)
// {
// }

// void usbd_cdc_acm_set_dtr(uint8_t intf, bool dtr)
// {
//     USB_LOG_INFO("intf:%u, dtr:%d\r\n", intf, dtr);
// }

// void usbd_cdc_acm_set_rts(uint8_t intf, bool rts)
// {
//     USB_LOG_INFO("intf:%u, rts:%d\r\n", intf, rts);
// }

static void la_cdc_acm_data_send_with_dtr_test(void)
{
    if (ring_buffer_is_empty(&cdc_write_ring_buffer))
    {
        return;
    }

    if (la_ep_tx_busy_flag == false)
    {
        la_ep_tx_busy_flag = true;
        /*!< Send */
        write_buffer_len = ring_buffer_num_items(&cdc_write_ring_buffer);
        ring_buffer_dequeue_arr(&cdc_write_ring_buffer, (char *)write_buffer, write_buffer_len);
        usbd_ep_start_write(CDC_IN_EP, write_buffer, write_buffer_len);
        write_buffer_len = 0;
        while (la_ep_tx_busy_flag)
        {
            vTaskDelay(1);
        }
    }
}

#include "dap_main.h"

static void logic_analyzer_main_task(void *pvParameter)
{
    // Initialize the USB driver and CDC interface
    cdc_uart_enable(false);
    ring_buffer_init(&cdc_write_ring_buffer);
    ring_buffer_init(&cdc_read_ring_buffer);
    cdc_acm_init();
    ESP_LOGI(TAG, "usb cdc acm init done");

    while (1)
    {
        // Send back the data received from the host
        la_cdc_acm_data_send_with_dtr_test();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

static TaskHandle_t *xHandle_LA_CDC = NULL;

int logic_analyzer_cdc_start(void)
{
    if (xHandle_LA_CDC != NULL)
    {
        vTaskDelete(xHandle_LA_CDC);
    }
    xTaskCreate(logic_analyzer_main_task, "LA_CDC task", 1024 * 4, NULL, 5, xHandle_LA_CDC);
    return 1;
}

int logic_analyzer_cdc_stop(void)
{
    if (xHandle_LA_CDC != NULL)
    {
        vTaskDelete(xHandle_LA_CDC);
    }
    usbd_deinitialize();
    usb_esp_jtag_serial_enable();
    return 1;
}

void logic_analyzer_cdc_read(const uint8_t *data, uint32_t data_len)
{
    ring_buffer_dequeue_arr(&cdc_read_ring_buffer, (char *)data, data_len);
}

void logic_analyzer_cdc_write(const uint8_t *data, uint32_t data_len)
{
    ring_buffer_queue_arr(&cdc_write_ring_buffer, (char *)data, data_len);
}

#define BLOCK_SIZE 512
#define BLOCK_COUNT 10

typedef struct
{
    uint8_t BlockSpace[BLOCK_SIZE];
} BLOCK_TYPE;

BLOCK_TYPE mass_block[BLOCK_COUNT];

void usbd_msc_get_cap(uint8_t lun, uint32_t *block_num, uint16_t *block_size)
{
    *block_num = 1000; // Pretend having so many buffer,not has actually.
    *block_size = BLOCK_SIZE;
}
int usbd_msc_sector_read(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    if (sector < 10)
        memcpy(buffer, mass_block[sector].BlockSpace, length);
    return 0;
}

int usbd_msc_sector_write(uint32_t sector, uint8_t *buffer, uint32_t length)
{
    if (sector < 10)
        memcpy(mass_block[sector].BlockSpace, buffer, length);
    return 0;
}