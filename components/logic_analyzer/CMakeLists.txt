# set( srcs 
#     logic_analyzer_hal/logic_analyzer_hal.c
#     logic_analyzer_cdc/logic_analyzer_cdc.c
# )
# set( includedir 
#     logic_analyzer_hal/include
#     logic_analyzer_cdc 
#     )
# set( priv_includedir 
#     logic_analyzer_hal/private_include 
#     )
# set( priv_require 
#     driver
#     esp_eth 
#     esp_mm
#     esp_psram 
#     )

# set( require 
#     driver
#     usb
#     usb_cherry
#     )


# list(APPEND srcs
#         logic_analyzer_hal/esp32s3/logic_analyzer_ll.c      
#     )
# list(APPEND priv_includedir
#         logic_analyzer_hal/esp32s3/private_include
#     )
# if(CONFIG_ANALYZER_USE_HI_LEVEL_INTERRUPT)
#         list( APPEND srcs 
#             logic_analyzer_hal/esp32s3/logic_analyzer_triggered_isr_start.c
#             logic_analyzer_hal/esp32s3/logic_analyzer_hi_interrupt_handler.s 
#             )
#     endif()




# list( APPEND srcs
#         logic_analyzer_sump/logic_analyzer_sump.c
#     )
# list( APPEND includedir 
#         logic_analyzer_sump/include 
#     )
# list( APPEND priv_includedir 
#         logic_analyzer_sump/private_include 
#     )


# idf_component_register(
#     SRCS ${srcs}
#     INCLUDE_DIRS  ${includedir}
#     PRIV_INCLUDE_DIRS ${priv_includedir}
#     REQUIRES ${require}
#     PRIV_REQUIRES ${priv_require}
#     EMBED_FILES ${embed}
# )


file(GLOB_RECURSE SOURCES  
    "logic_analyzer_hal/logic_analyzer_hal.c"
    "logic_analyzer_cdc/logic_analyzer_cdc.c"
    "logic_analyzer_hal/esp32s3/logic_analyzer_ll.c"
    "logic_analyzer_hal/esp32s3/logic_analyzer_triggered_isr_start.c"
    "logic_analyzer_hal/esp32s3/logic_analyzer_hi_interrupt_handler.s"
    "logic_analyzer_sump/logic_analyzer_sump.c"
)

set(includes 
    "."
    "logic_analyzer_hal/include"
    "logic_analyzer_hal/private_include"
    "logic_analyzer_hal/esp32s3/private_include"
    "logic_analyzer_sump/include"
    "logic_analyzer_sump/private_include"
    "logic_analyzer_cdc"
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS "." ${includes}
    REQUIRES 
        driver
        usb
        usb_cherry
        esp_mm
        esp_psram 
        ring_buffer

)



if(CONFIG_ANALYZER_USE_HI_LEVEL_INTERRUPT)
        target_link_libraries(${COMPONENT_LIB} INTERFACE "-u la_include_hi_interrupt")
 endif()
