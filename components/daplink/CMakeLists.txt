
file(GLOB_RECURSE SOURCES  
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
)

set(includes 
    "."
    "daplink/ring_buffer"
    "daplink/port"
    "daplink/DAP/Include"
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS "." ${includes}
    REQUIRES 
        driver
        usb
        usb_cherry
)



