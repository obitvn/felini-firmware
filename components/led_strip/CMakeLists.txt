idf_component_register(
    SRCS led_strip_encoder.c
    INCLUDE_DIRS .
    REQUIRES log i2c_manager driver 
)
