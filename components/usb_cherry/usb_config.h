#ifndef _USB_CONFIG_H
#define _USB_CONFIG_H

#include "esp_log.h"

// depends on the platform
#define log_info_interrupt_d(format_pc, ...) ESP_EARLY_LOGI(__FUNCTION__, format_pc, ##__VA_ARGS__)
#define USB_BASE 0x60080000
#define CONFIG_USB_DWC2_PORT FS_PORT
#define CONFIG_USB_PRINTF log_info_interrupt_d

#define usb_malloc(size) malloc(size)
#define usb_free(ptr) free(ptr)

/* USB common Configuration */
#ifndef CONFIG_USB_DBG_LEVEL
#define CONFIG_USB_DBG_LEVEL USB_DBG_INFO
#endif

#ifndef CONFIG_USB_PRINTF
#define CONFIG_USB_PRINTF printf
#endif

#define CONFIG_USB_PRINTF_COLOR_ENABLE

/* attribute data into no cache ram */
#define USB_NOCACHE_RAM_SECTION

#ifndef CONFIG_USB_ALIGN_SIZE
#define CONFIG_USB_ALIGN_SIZE 64
#endif

#ifndef USB_NUM_BIDIR_ENDPOINTS
#define USB_NUM_BIDIR_ENDPOINTS 8 /* define with minimum value*/
#endif

/* USB DEVICE Configuration */
/* core */
#ifndef CONFIG_USBDEV_REQUEST_BUFFER_LEN
#define CONFIG_USBDEV_REQUEST_BUFFER_LEN 256
#endif

#ifndef CONFIG_USBDEV_DESC_CHECK
#define CONFIG_USBDEV_DESC_CHECK 0
#endif

#ifndef CONFIG_USBDEV_TEST_MODE
#define CONFIG_USBDEV_TEST_MODE 0
#endif

/* cdc class */
// #define CONFIG_USBDEV_CDC_ACM_UART

/* msc class */

#ifndef CONFIG_USBDEV_MSC_BLOCK_SIZE
#define CONFIG_USBDEV_MSC_BLOCK_SIZE 512
#endif

#ifndef CONFIG_USBDEV_MSC_MANUFACTURER_STRING
#define CONFIG_USBDEV_MSC_MANUFACTURER_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_PRODUCT_STRING
#define CONFIG_USBDEV_MSC_PRODUCT_STRING ""
#endif

#ifndef CONFIG_USBDEV_MSC_VERSION_STRING
#define CONFIG_USBDEV_MSC_VERSION_STRING "0.01"
#endif

// #define CONFIG_USBDEV_MSC_THREAD

#ifdef CONFIG_USBDEV_MSC_THREAD
#ifndef CONFIG_USBDEV_MSC_STACKSIZE
#define CONFIG_USBDEV_MSC_STACKSIZE 2048
#endif

#ifndef CONFIG_USBDEV_MSC_PRIO
#define CONFIG_USBDEV_MSC_PRIO 4
#endif
#endif

/* audio class */
#ifndef CONFIG_USBDEV_AUDIO_VERSION
#define CONFIG_USBDEV_AUDIO_VERSION 0x0100
#endif

#ifndef CONFIG_USBDEV_AUDIO_MAX_CHANNEL
#define CONFIG_USBDEV_AUDIO_MAX_CHANNEL 2
#endif

/* USB HOST Configuration */
#ifndef CONFIG_USBHOST_RHPORTS
#define CONFIG_USBHOST_RHPORTS 1
#endif

#ifndef CONFIG_USBHOST_EHPORTS
#define CONFIG_USBHOST_EHPORTS 4
#endif

#ifndef CONFIG_USBHOST_PIPE_NUM
#define CONFIG_USBHOST_PIPE_NUM 10
#endif

#ifndef CONFIG_USBHOST_INTF_NUM
#define CONFIG_USBHOST_INTF_NUM 6
#endif

#ifndef CONFIG_USBHOST_EP_NUM
#define CONFIG_USBHOST_EP_NUM 4
#endif

#ifndef CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT
#define CONFIG_USBHOST_CONTROL_TRANSFER_TIMEOUT 5000
#endif

#ifndef CONFIG_USBHOST_MSC_TIMEOUT
#define CONFIG_USBHOST_MSC_TIMEOUT 5000
#endif

#ifndef CONFIG_USBHOST_HPWORKQ_PRIO
#define CONFIG_USBHOST_HPWORKQ_PRIO 5
#endif
#ifndef CONFIG_USBHOST_HPWORKQ_STACKSIZE
#define CONFIG_USBHOST_HPWORKQ_STACKSIZE 2048
#endif

#ifndef CONFIG_USBHOST_LPWORKQ_PRIO
#define CONFIG_USBHOST_LPWORKQ_PRIO 1
#endif
#ifndef CONFIG_USBHOST_LPWORKQ_STACKSIZE
#define CONFIG_USBHOST_LPWORKQ_STACKSIZE 2048
#endif

#ifndef CONFIG_USBHOST_PSC_PRIO
#define CONFIG_USBHOST_PSC_PRIO 4
#endif
#ifndef CONFIG_USBHOST_PSC_STACKSIZE
#define CONFIG_USBHOST_PSC_STACKSIZE 4096
#endif

#ifndef CONFIG_USBHOST_DEV_NAMELEN
#define CONFIG_USBHOST_DEV_NAMELEN 16
#endif

#define CONFIG_USBHOST_ASYNCH
// #define CONFIG_USBHOST_GET_STRING_DESC

/* EHCI Configuration */
#define CONFIG_USB_EHCI_HCCR_BASE (0x20072000)
#define CONFIG_USB_EHCI_HCOR_BASE (0x20072000 + 0x10)
#define CONFIG_USB_EHCI_QH_NUM (10)
#define CONFIG_USB_EHCI_QTD_NUM (10)
// #define CONFIG_USB_EHCI_INFO_ENABLE
#define CONFIG_USB_ECHI_HCOR_RESERVED_DISABLE
// #define CONFIG_USB_EHCI_CONFIGFLAG

#endif