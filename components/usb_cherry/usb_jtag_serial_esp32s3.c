
#include "usb_jtag_serial_esp32s3.h"

#include "esp_intr_alloc.h"
#include "soc/usb_periph.h"
#include "soc/periph_defs.h"
#include "esp_private/usb_phy.h"
#include "driver/usb_serial_jtag.h"

#include "hal/usb_serial_jtag_ll.h"
#include "hal/usb_phy_ll.h"

void usb_esp_jtag_serial_enable(void)
{
    usb_phy_ll_int_jtag_enable(&USB_SERIAL_JTAG);
}

void usb_esp_jtag_serial_disable(void)
{
    
}