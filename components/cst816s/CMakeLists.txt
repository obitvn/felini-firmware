idf_component_register(SRCS "cst816s.c" "cst816s_touch_driver.c"
                        INCLUDE_DIRS "."
                        REQUIRES driver
                        i2c_manager
                        lvgl
                        )

