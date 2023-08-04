/**
 ******************************************************************************
 * @file          main.c
 * @brief         简述
 * @author        LiGuo
 *                1570139720@qq.com
 * @version       1.0
 * @date          2022.09.25
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright 2021 LiGuo.
 * All rights reserved.</center></h2>
 *
 * @htmlonly
 * <span style='font-weight: bold'>History</span>
 * @endhtmlonly
 * 版本|作者|时间|描述
 * ----|----|----|----
 * 1.0|LiGuo|2022.09.25|创建文件
 ******************************************************************************
 */
#include "usbd_core.h"
#include "usb_config.h"
#include "usbd_cdc.h"
#include "DAP_config.h"
#include "port_common.h"
#include "ringbuffer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <stdio.h>

#define CDC_IN_EP 0x81
#define CDC_OUT_EP 0x04
#define CDC_INT_EP 0x83

#define CMSIS_DAP_EP_RECV 0x01
#define CMSIS_DAP_EP_SEND 0x82

#define USBD_VID 0xd6e7
#define USBD_PID 0x3507
#define USBD_MAX_POWER 500
#define USBD_LANGID_STRING 1033

#define CMSIS_DAP_INTERFACE_SIZE (9 + 7 + 7)
#define USB_CONFIG_SIZE (9 + CMSIS_DAP_INTERFACE_SIZE + CDC_ACM_DESCRIPTOR_LEN)

const uint8_t rv_dap_plus_descriptor[] = {
    USB_DEVICE_DESCRIPTOR_INIT(USB_2_0, 0xEF, 0x02, 0x01, USBD_VID, USBD_PID, 0x0100, 0x01),
    /* Configuration 0 */
    USB_CONFIG_DESCRIPTOR_INIT(USB_CONFIG_SIZE, 0x03, 0x01, USB_CONFIG_BUS_POWERED, USBD_MAX_POWER),
    /* Interface 0 */
    USB_INTERFACE_DESCRIPTOR_INIT(0x00, 0x00, 0x02, 0xFF, 0x00, 0x00, 0x04),
    /* Endpoint OUT 1 */
    USB_ENDPOINT_DESCRIPTOR_INIT(CMSIS_DAP_EP_RECV, USB_ENDPOINT_TYPE_BULK, 0x40, 0x00),
    /* Endpoint IN 2 */
    USB_ENDPOINT_DESCRIPTOR_INIT(CMSIS_DAP_EP_SEND, USB_ENDPOINT_TYPE_BULK, 0x40, 0x00),
    CDC_ACM_DESCRIPTOR_INIT(0x01, CDC_INT_EP, CDC_OUT_EP, CDC_IN_EP, 0x00),
    /* String 0 (LANGID) */
    USB_LANGID_INIT(USBD_LANGID_STRING),
    /* String 1 (Manufacturer) */
    0x12,                       /* bLength */
    USB_DESCRIPTOR_TYPE_STRING, /* bDescriptorType */
    'P', 0x00,                  /* wcChar0 */
    'l', 0x00,                  /* wcChar1 */
    'u', 0x00,                  /* wcChar2 */
    'm', 0x00,                  /* wcChar3 */
    'l', 0x00,                  /* wcChar4 */
    'i', 0x00,                  /* wcChar5 */
    'n', 0x00,                  /* wcChar6 */
    'k', 0x00,                  /* wcChar7 */
    /* String 2 (Product) */
    0x22,                       // bLength
    USB_DESCRIPTOR_TYPE_STRING, // bDescriptorType
    'F', 0,                     // wcChar0
    'e', 0,                     // wcChar1
    'l', 0,                     // wcChar2
    'i', 0,                     // wcChar3
    'n', 0,                     // wcChar4
    'i', 0,                     // wcChar5
    ' ', 0,                     // wcChar6
    'C', 0,                     // wcChar7
    'M', 0,                     // wcChar8
    'S', 0,                     // wcChar9
    'I', 0,                     // wcChar10
    'S', 0,                     // wcChar11
    '-', 0,                     // wcChar12
    'D', 0,                     // wcChar13
    'A', 0,                     // wcChar14
    'P', 0,                     // wcChar15
    /* String 3 (Serial Number) */
    0x1A,                       // bLength
    USB_DESCRIPTOR_TYPE_STRING, // bDescriptorType
    '0', 0,                     // wcChar0
    '1', 0,                     // wcChar1
    '2', 0,                     // wcChar2
    '3', 0,                     // wcChar3
    '4', 0,                     // wcChar4
    '5', 0,                     // wcChar5
    'A', 0,                     // wcChar6
    'B', 0,                     // wcChar7
    'C', 0,                     // wcChar8
    'D', 0,                     // wcChar9
    'E', 0,                     // wcChar10
    'F', 0,                     // wcChar11
    /* String 4 (Interface) */
    0x22,                       // bLength
    USB_DESCRIPTOR_TYPE_STRING, // bDescriptorType
    'F', 0,                     // wcChar0
    'e', 0,                     // wcChar1
    'l', 0,                     // wcChar2
    'i', 0,                     // wcChar3
    'n', 0,                     // wcChar4
    'i', 0,                     // wcChar5
    ' ', 0,                     // wcChar6
    'C', 0,                     // wcChar7
    'M', 0,                     // wcChar8
    'S', 0,                     // wcChar9
    'I', 0,                     // wcChar10
    'S', 0,                     // wcChar11
    '-', 0,                     // wcChar12
    'D', 0,                     // wcChar13
    'A', 0,                     // wcChar14
    'P', 0,                     // wcChar15
#ifdef CONFIG_USB_HS
    /* Device Qualifier */
    0x0a,
    USB_DESCRIPTOR_TYPE_DEVICE_QUALIFIER,
    0x10,
    0x02,
    0x00,
    0x00,
    0x00,
    0x40,
    0x01,
    0x00,
#endif
    /* End */
    0x00};

extern void usb_dap_recv_callback(uint8_t ep, uint32_t nbytes);
extern void usb_dap_send_callback(uint8_t ep, uint32_t nbytes);
struct usbd_interface dap_interface;

static struct usbd_endpoint dap_endpoint_recv = {
    .ep_addr = CMSIS_DAP_EP_RECV,
    .ep_cb = usb_dap_recv_callback};
static struct usbd_endpoint dap_endpoint_send = {
    .ep_addr = CMSIS_DAP_EP_SEND,
    .ep_cb = usb_dap_send_callback};

uint8_t cdc_read_buffer[64];
ring_buffer_t uart_ring_buffer;
ring_buffer_t cdc_ring_buffer;
struct cdc_line_coding dap_line_coding;

extern uint8_t USB_Request[DAP_PACKET_SIZE];
volatile bool ep_tx_busy_flag = false;

#ifdef CONFIG_USB_HS
#define CDC_MAX_MPS 512
#else
#define CDC_MAX_MPS 64
#endif

__WEAK void dap_uart_send_from_ringbuff(void)
{
}

__WEAK void dap_uart_config(uint32_t baudrate, uint8_t databits, uint8_t parity, uint8_t stopbits)
{
}

void dap_line_coding_init(void)
{
    dap_line_coding.dwDTERate = 115200;
    dap_line_coding.bDataBits = 8;
    dap_line_coding.bParityType = 0;
    dap_line_coding.bCharFormat = 0;
}

char send_buffer[RING_BUFFER_SIZE];
void dap_cdc_send_from_ringbuff(void)
{
    if (ring_buffer_is_empty(&uart_ring_buffer))
    {
        return;
    }

    if (ep_tx_busy_flag == false)
    {
        /*!< Send */
        uint16_t len = ring_buffer_num_items(&uart_ring_buffer);
        ring_buffer_dequeue_arr(&uart_ring_buffer, send_buffer, len);
        usbd_ep_start_write(CDC_IN_EP, (uint8_t *)send_buffer, len);
        ep_tx_busy_flag = true;
    }    
}

void usbd_configure_done_callback(void)
{
    /* setup first out ep read transfer */
    usbd_ep_start_read(CDC_OUT_EP, cdc_read_buffer, 64);
    usbd_ep_start_read(CMSIS_DAP_EP_RECV, USB_Request, DAP_PACKET_SIZE);
}

void usbd_cdc_acm_bulk_out(uint8_t ep, uint32_t nbytes)
{
    /* setup next out ep read transfer */
    ring_buffer_queue_arr(&cdc_ring_buffer, (char *)cdc_read_buffer, nbytes);
    usbd_ep_start_read(CDC_OUT_EP, cdc_read_buffer, 64);
}

void usbd_cdc_acm_bulk_in(uint8_t ep, uint32_t nbytes)
{
    if ((nbytes % CDC_MAX_MPS) == 0 && nbytes)
    {
        /* send zlp */
        usbd_ep_start_write(CDC_IN_EP, NULL, 0);
    }
    else
    {
        ep_tx_busy_flag = false;
    }
}

void usbd_cdc_acm_set_line_coding(uint8_t intf, struct cdc_line_coding *line_coding)
{
    dap_line_coding.dwDTERate = line_coding->dwDTERate;
    dap_line_coding.bDataBits = line_coding->bDataBits;
    dap_line_coding.bParityType = line_coding->bParityType;
    dap_line_coding.bCharFormat = line_coding->bCharFormat;
    dap_uart_config(line_coding->dwDTERate, line_coding->bDataBits,
                    line_coding->bParityType, line_coding->bCharFormat);
}

void usbd_cdc_acm_get_line_coding(uint8_t intf, struct cdc_line_coding *line_coding)
{
    line_coding->dwDTERate = dap_line_coding.dwDTERate;
    line_coding->bDataBits = dap_line_coding.bDataBits;
    line_coding->bParityType = dap_line_coding.bParityType;
    line_coding->bCharFormat = dap_line_coding.bCharFormat;
}

void usbd_cdc_acm_set_dtr(uint8_t intf, bool dtr)
{
    // if (dtr) {
    //     dtr_enable = 1;
    // } else {
    //     dtr_enable = 0;
    // }
    // // dtr_pin_set(!dtr);
}

static struct usbd_endpoint cdc_out_ep = {
    .ep_addr = CDC_OUT_EP,
    .ep_cb = usbd_cdc_acm_bulk_out};

static struct usbd_endpoint cdc_in_ep = {
    .ep_addr = CDC_IN_EP,
    .ep_cb = usbd_cdc_acm_bulk_in};

extern void dap_process(void);
extern struct usb_msosv1_descriptor msosv1_desc;

struct usbd_interface intf0;
struct usbd_interface intf1;

static void daplink_task(void *pvParameter)
{
    dap_platform_init();
    dap_line_coding_init();
    usbd_desc_register(rv_dap_plus_descriptor);
    usbd_msosv1_desc_register(&msosv1_desc); /*register winusb*/

    /*!< winusb */
    usbd_add_interface(&dap_interface);
    usbd_add_endpoint(&dap_endpoint_recv);
    usbd_add_endpoint(&dap_endpoint_send);

    /*!< cdc acm */
    usbd_add_interface(usbd_cdc_acm_init_intf(&intf0));
    usbd_add_interface(usbd_cdc_acm_init_intf(&intf1));
    usbd_add_endpoint(&cdc_out_ep);
    usbd_add_endpoint(&cdc_in_ep);

    dap_gpio_init();
    usbd_initialize();
    printf("init!\n");

    while (!usb_device_is_configured())
    {
        printf(".");
        vTaskDelay(100);
    }

    printf("Config done!\n");

    while (1)
    {
        dap_process();
        dap_cdc_send_from_ringbuff();
        dap_uart_send_from_ringbuff();
        vTaskDelay(pdMS_TO_TICKS(10));
        // printf("-");
    }
}

TaskHandle_t xHandle_DAPLink;

int daplink_start(void)
{
    xTaskCreatePinnedToCore(daplink_task, "DAPLink task", 1024 * 2, NULL, 1, xHandle_DAPLink, 0);
    return 1;
}

int daplink_stop(void)
{
    printf("Delete DAPLink task!\n");
    vTaskDelete(xHandle_DAPLink);
}

/************************ (C) COPYRIGHT 2021 LiGuo *****END OF FILE*************/
