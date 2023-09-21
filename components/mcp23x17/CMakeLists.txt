idf_component_register(
    SRCS mcp23x17.c
    INCLUDE_DIRS .
    REQUIRES driver i2c_manager 
)
