#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

    void logic_analyzer_sump(void);
    void la_usb_init(void);
    void la_usb_denit(void);
    void la_usbcdc_write(void);
    void la_usbcdc_read(void);

#ifdef __cplusplus
}
#endif
