file(GLOB_RECURSE SOURCES  
    "addition/usb_cherry_platform.c"
    "CherryUSB/class/cdc/usbd_cdc.c"
    "CherryUSB/class/msc/usbd_msc.c"
    "CherryUSB/core/usbd_core.c"
    "CherryUSB/port/dwc2/usb_dc_dwc2.c"
)

set(includes 
    "CherryUSB/class/cdc"
    "CherryUSB/class/msc"
    "CherryUSB/common"
    "CherryUSB/core"
    "CherryUSB/port/dwc2"
)

idf_component_register(
    SRCS "winusb.c" ${SOURCES}
    INCLUDE_DIRS "." ${includes}
    REQUIRES 
        driver
        usb
)
