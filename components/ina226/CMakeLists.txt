idf_component_register(
    SRCS ina226.c
    INCLUDE_DIRS .
    REQUIRES log i2c_manager
)
