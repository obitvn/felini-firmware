#ifndef _ESP_JTAG_SERIAL_H_
#define _ESP_JTAG_SERIAL_H_

#include "esp_intr_alloc.h"
#include "soc/usb_periph.h"
#include "soc/periph_defs.h"
#include "esp_private/usb_phy.h"
#include "driver/usb_serial_jtag.h"



#ifdef __cplusplus
extern "C" {
#endif


void usb_esp_jtag_serial_enable(void)
{
	usb_serial_jtag_driver_config_t usb_serial_jtag_config = USB_SERIAL_JTAG_DRIVER_CONFIG_DEFAULT();
    /* Install USB-SERIAL-JTAG driver for interrupt-driven reads and writes */
    esp_err_t ret = ESP_OK;
    ret = usb_serial_jtag_driver_install(&usb_serial_jtag_config);
    printf("chery reinstall USB-SERIAL-JTAG driver\r\n");
    if (ret != ESP_OK)
    {
        printf("error usb jtag\n");
    }
}


#ifdef __cplusplus
}
#endif

#endif