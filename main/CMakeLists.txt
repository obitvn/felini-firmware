


# file(GLOB_RECURSE SOURCES  "porting/*.c" ./App/*.c ./App/*.cpp ./App/Common/**/*.c ./App/Common/**/*.cpp
#                            ./App/Pages/*.c ./App/Pages/**/*.c ./App/Pages/**/*.cpp
#                            ./App/Resource/*.c ./App/Resource/*.cpp /App/Resource/**/*.c ./App/Resource/**/*.cpp
#                            ./App/Utils/**.c ./App/Utils/**.cpp ./HAL/*.c ./HAL/*.cpp)


# set(includes 
#     "porting"
#      "." 
#      "./App" 
#      "./HAL"
#      )

# idf_component_register(SRCS "main.cpp" "${SOURCES}"
#                     INCLUDE_DIRS "." ${includes}

#     REQUIRES 
#         lvgl
#         lvgl_disp_port
#         )

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

set(includes 
    "porting"
    "."
    "./App"
    "./HAL"
)

idf_component_register(
    SRCS "main.cpp" ${SOURCES}
    INCLUDE_DIRS "." ${includes}
    REQUIRES 
        lvgl
        lvgl_disp_port
        driver
)

