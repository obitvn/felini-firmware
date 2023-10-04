

file(GLOB_RECURSE SOURCES  
    "porting/*.c"
    "./App/*.c"
    "./App/*.cpp"
    "./App/Common/**/*.c"
    "./App/Common/**/*.cpp"
    "./App/Pages/*.c"
    "./App/Pages/**/*.c"
    "./App/Pages/**/*.cpp"
    "./App/Resource/*.c"
    "./App/Resource/*.cpp"
    "./App/Resource/**/*.c"
    "./App/Resource/**/*.cpp"
    "./App/Utils/**.c"
    "./App/Utils/**.cpp"
    "./HAL/*.c"
    "./HAL/*.cpp"
)

# Tìm các tệp trong thư mục HAL/HAL_SIM và loại trừ chúng
file(GLOB_RECURSE HAL_SIM_SOURCES "./HAL/HAL_SIM/*.c" "./HAL/HAL_SIM/*.cpp")
list(REMOVE_ITEM SOURCES ${HAL_SIM_SOURCES})


set(includes 
    "porting"
    "."
    "./App"
    "./HAL"
)

idf_component_register(
    SRCS "main.cpp" ${SOURCES}
    INCLUDE_DIRS  ${includes}
    REQUIRES 
        lvgl
        lvgl_disp_port
        lvgl_indev_port
        driver
        esp_timer
        usb
        axp173
        fusb302
        ina226
        daplink
        usb_cherry
        logic_analyzer
        axp192
        mcp23x17
        i2c_manager
        led_strip
        esp_hw_support
        freqcount

)



