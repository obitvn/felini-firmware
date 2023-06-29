idf_component_register(
    SRCS 
        "lvgl_indev_port.c"
        
    INCLUDE_DIRS 
        "."

    REQUIRES 
        lvgl
        encoder
        lvgl_esp32_drivers)
