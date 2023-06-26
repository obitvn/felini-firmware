
file(GLOB srcs
 "porting/*.c"
    )

set(includes 
    "porting")

idf_component_register(SRCS "main.cpp" "${srcs}" 
                    INCLUDE_DIRS "." ${includes}

    REQUIRES 
        lvgl
        lvgl_disp_port
        )


