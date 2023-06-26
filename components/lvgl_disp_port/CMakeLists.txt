idf_component_register(
    SRCS "lvgl_disp_port.c"
       
    INCLUDE_DIRS 
        "."
    REQUIRES 
        lvgl 
        lvgl_esp32_drivers)
