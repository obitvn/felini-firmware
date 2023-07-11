


# file(GLOB_RECURSE SOURCES  "porting/*.c" ./App/*.c ./App/*.cpp ./App/Common/**/*.c ./App/Common/**/*.cpp
#                            ./App/Pages/*.c ./App/Pages/**/*.c ./App/Pages/**/*.cpp
#                            ./App/Resource/*.c ./App/Resource/*.cpp /App/Resource/**/*.c ./App/Resource/**/*.cpp
#                            ./App/Utils/**.c ./App/Utils/**.cpp ./HAL/*.c ./HAL/*.cpp)


# set(includes 
#     "porting"
#      "." 
#      "./App" 
#      "./HAL"
#      )

# idf_component_register(SRCS "main.cpp" "${SOURCES}"
#                     INCLUDE_DIRS "." ${includes}

#     REQUIRES 
#         lvgl
#         lvgl_disp_port
#         )

file(GLOB_RECURSE SOURCES  
    "porting/*.c"
    "./App/*.c"
    "./App/*.cpp"
    "./App/Common/**/*.c"
    "./App/Common/**/*.cpp"
    "./App/Pages/*.c"
    "./App/Pages/**/*.c"
    "./App/Pages/**/*.cpp"
    "./App/Resource/*.c"
    "./App/Resource/*.cpp"
    "./App/Resource/**/*.c"
    "./App/Resource/**/*.cpp"
    "./App/Utils/**.c"
    "./App/Utils/**.cpp"
    "./HAL/*.c"
    "./HAL/*.cpp"

    "dap_main.c"
    "dap_process.c"
    "winusb.c"

    "daplink/ring_buffer/ringbuffer.c"
    "daplink/port/port_core.c"
    "daplink/DAP/Source/DAP_vendor.c"
    "daplink/DAP/Source/DAP.c"
    "daplink/DAP/Source/JTAG_DP.c"
    "daplink/DAP/Source/SW_DP.c"
    "daplink/DAP/Source/SWO.c"
    "daplink/DAP/Source/UART.c"

    "usb_cherry/addition/usb_cherry_platform.c"
    "usb_cherry/CherryUSB/class/cdc/usbd_cdc.c"
    "usb_cherry/CherryUSB/class/msc/usbd_msc.c"
    "usb_cherry/CherryUSB/core/usbd_core.c"
    "usb_cherry/CherryUSB/port/dwc2/usb_dc_dwc2.c"
)

set(includes 
    "porting"
    "."
    "./App"
    "./HAL"

    "daplink/ring_buffer"
    "daplink/port"
    "daplink/DAP/Include"

    # "usb_cherry/addition"
    "usb_cherry/CherryUSB/class/cdc"
    "usb_cherry/CherryUSB/class/msc"
    "usb_cherry/CherryUSB/common"
    "usb_cherry/CherryUSB/core"
    "usb_cherry/CherryUSB/port/dwc2"
)

idf_component_register(
    SRCS "main.cpp" ${SOURCES}
    INCLUDE_DIRS "." ${includes}
    REQUIRES 
        lvgl
        lvgl_disp_port
        lvgl_esp32_drivers
        lvgl_indev_port
        driver
        usb
)

