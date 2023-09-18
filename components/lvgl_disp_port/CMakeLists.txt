idf_component_register(
    SRCS "lvgl_disp_port.cpp"
       
    INCLUDE_DIRS 
        "."
    REQUIRES 
        lvgl 
        driver
        LovyanGFX
        )
