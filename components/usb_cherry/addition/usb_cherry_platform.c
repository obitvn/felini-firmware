#include "esp_intr_alloc.h"
#include "soc/usb_periph.h"
#include "soc/periph_defs.h"
#include "esp_private/usb_phy.h"
#include "driver/usb_serial_jtag.h"

uint32_t SystemCoreClock = 160 * 1000000; // dwc2 的一个参数

static intr_handle_t interrupt_handle_ps; // esp32 中断要用

void usb_dc_low_level_init(void)
{
    printf("install USB-SERIAL-JTAG driver\r\n");
    void usb_interrupt_enable();

    // esp32s2 phy
    static usb_phy_handle_t handle_s;
    usb_phy_config_t config_s = {
        .controller = USB_PHY_CTRL_OTG,
        .otg_mode = USB_OTG_MODE_DEVICE,
        .target = USB_PHY_TARGET_INT};
    usb_new_phy(&config_s, &handle_s);

    usb_interrupt_enable();
}

void usb_dc_low_level_deinit(void)
{
    
}

// usb 中断
static void usb_interrupt_cb(void *arg_pv)
{
    extern void OTG_FS_IRQHandler(); // dwc2 的中断处理函数

    OTG_FS_IRQHandler();
}

// usb 中断开启
void usb_interrupt_enable()
{
    esp_intr_alloc(ETS_USB_INTR_SOURCE, ESP_INTR_FLAG_LOWMED, (intr_handler_t)usb_interrupt_cb, 0, &interrupt_handle_ps);
}

// usb 中断关闭
void usb_interrupt_disable()
{
    esp_intr_free(interrupt_handle_ps);
}