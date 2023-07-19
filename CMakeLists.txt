# # For more information about build system see
# # https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# # The following five lines of boilerplate have to be in your project's
# # CMakeLists in this exact order for cmake to work correctly
# # CMAKE_GENERATOR="Ninja"            - Khi gọi từ esp-idf
# # CMAKE_GENERATOR="MinGW Makefiles"  - Khi gọi từ VSCode build



# cmake_minimum_required(VERSION 3.12.4)
# include(CMakePrintHelpers)
# set(CMAKE_C_STANDARD 17)
# set(CMAKE_CXX_STANDARD 20)
# string(ASCII 27 ESCAPE)



# if("${CMAKE_GENERATOR}" MATCHES "MinGW Makefiles")
#     project(Tinybench)
#     message("${ESCAPE}[34mBuilding from VSCode - Generate simulate file${ESCAPE}[0m")
#     # Add VSCode-specific options here
#     add_compile_definitions(LVGL_VSCode_SIM)
#     include(CTest)
#     enable_testing()
#     # change build dir
#     # set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build-sim)
#     # set(CMAKE_BUILD_DIRECTORY ${CMAKE_BINARY_DIR})
#     # add macro definition
#     add_definitions(-DUSE_SDL)
#     # add_executable(Tinybench-s main.cpp)
#     # Add header file directory
#     include_directories(main)
#     include_directories("main/App" )
#     include_directories("main/App/Common")
#     include_directories("main/App/Config")
#     include_directories("main/App/Pages")
#     include_directories("main/App/Pages/_Template")
#     include_directories("main/App/Pages/StartUp")
#     include_directories("main/App/Pages/StatusBar")
#     include_directories("main/App/Pages/Weather")
#     include_directories("main/App/Resource")
#     include_directories("main/App/Resource/Font")
#     include_directories("main/App/Resource/Image")
#     include_directories("main/App/Utils")
#     include_directories("main/App/Utils/DataCenter")
#     include_directories("main/App/Utils/PingPongBuffer")
#     include_directories("main/App/Utils/Filter")
#     include_directories("main/App/Utils/lv_allocator")
#     include_directories("main/App/Utils/lv_ext")
#     include_directories("main/App/Utils/lv_lib_png")
#     include_directories("main/App/Utils/lv_monkey")
#     include_directories("main/App/Utils/lv_poly_line")
#     include_directories("main/App/Utils/PageManager")
#     include_directories("main/HAL")
#     # include_directories("main/HAL")
#     # include_directories("./App/Utils/DataCenter")
#     # Add sub-library compilation
#     add_subdirectory("lvgl")
#     add_subdirectory("lv_drivers")
#     # Add source files (recursively included)s
#     FILE(GLOB_RECURSE src_source "main/*.c" 
#     "main/main.cpp"  
#     "main/App/*.c"
#     "main/App/*.cpp"
#     "main/App/Common/**/*.c"
#     "main/App/Common/**/*.cpp"
#     "main/App/Pages/*.c"
#     "main/App/Pages/**/*.c"
#     "main/App/Pages/**/*.cpp"
#     "main/App/Resource/*.c"
#     "main/App/Resource/*.cpp"
#     "main/App/Resource/**/*.c"
#     "main/App/Resource/**/*.cpp"
#     "main/App/Utils/**.c"
#     "main/App/Utils/**.cpp"
#     "main/HAL/*.c"
#     "main/HAL/*.cpp")
#     # Compile the executable
#     add_executable(${PROJECT_NAME} ${src_source})
#     # link library
#     target_link_libraries(${PROJECT_NAME} lvgl)
#     target_link_libraries(${PROJECT_NAME} lv_drivers)
#     target_link_libraries(${PROJECT_NAME} mingw32)
#     target_link_libraries(${PROJECT_NAME} SDL2main)
#     target_link_libraries(${PROJECT_NAME} SDL2)
#     # Copy the SDL2.dll file to the build directory
#     file(COPY SDL2.dll DESTINATION ../build)
#     set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#     set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#     include(CPack)
# else()
#     message("${ESCAPE}[32mBuilding from external terminal - Generate hex file${ESCAPE}[0m")
#     add_compile_definitions(CONFIG_IDF_TARGET_ESP32S3)
#     include($ENV{IDF_PATH}/tools/cmake/project.cmake)
#     set(EXTRA_COMPONENT_DIRS lvgl)
#     project(Tinybench)
#     # Add external terminal-specific options here
# endif()



# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
# CMAKE_GENERATOR="Ninja"            - Khi gọi từ esp-idf
# CMAKE_GENERATOR="MinGW Makefiles"  - Khi gọi từ VSCode build

cmake_minimum_required(VERSION 3.12.4)
include(CMakePrintHelpers)
set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
string(ASCII 27 ESCAPE)

if("${CMAKE_GENERATOR}" MATCHES "MinGW Makefiles")
    project(Tinybench)
    message("${ESCAPE}[34mBuilding from VSCode - Generate simulate file${ESCAPE}[0m")
    # Add VSCode-specific options here
    add_compile_definitions(LVGL_VSCode_SIM)
    include(CTest)
    enable_testing()
    # change build dir
    # set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build-sim)
    # set(CMAKE_BUILD_DIRECTORY ${CMAKE_BINARY_DIR})
    # add macro definition
    add_definitions(-DUSE_SDL)
    #add_definitions(-DLV_MEM_CUSTOM=0)
    # Add header file directory
    include_directories(main)
    include_directories(" main/App")
    include_directories(" main/App/Common")
    include_directories(" main/App/Common/DataProc")
    include_directories(" main/App/Common/HAL")
    include_directories(" main/App/Config")
    include_directories(" main/App/Pages")
    include_directories(" main/App/Pages/_Template")
    include_directories(" main/App/Pages/StartUp")
    include_directories(" main/App/Pages/StatusBar")
    include_directories(" main/App/Pages/MenuList")
    include_directories(" main/App/Pages/AppInfos")
    include_directories(" main/App/Pages/IICDiscovery")
    include_directories(" main/App/Pages/Dialplate")
    include_directories(" main/App/Pages/PowerSupply")
    include_directories(" main/App/Resource")
    include_directories(" main/App/Resource/Font")
    include_directories(" main/App/Resource/Image")
    include_directories(" main/App/Utils")
    include_directories(" main/App/Utils/DataCenter")
    include_directories(" main/App/Utils/PingPongBuffer")
    include_directories(" main/App/Utils/Filter")
    include_directories(" main/App/Utils/lv_allocator")
    include_directories(" main/App/Utils/lv_ext")
    include_directories(" main/App/Utils/lv_lib_png")
    include_directories(" main/App/Utils/lv_monkey")
    include_directories(" main/App/Utils/lv_poly_line")
    include_directories(" main/App/Utils/PageManager")
    include_directories(" main/HAL")
    include_directories(" main/porting")
    # Add sub-library compilation
    add_subdirectory("lvgl")
    add_subdirectory("lv_drivers")
    # Add source files (recursively included)
    file(GLOB_RECURSE src_source 
    "main/main.cpp"  
    "main/porting/*.c"
    "main/App/*.c"
    "main/App/*.cpp"
    "main/App/Common/**/*.c"
    "main/App/Common/**/*.cpp"
    "main/App/Pages/*.c"
    "main/App/Pages/**/*.c"
    "main/App/Pages/**/*.cpp"
    "main/App/Resource/*.c"
    "main/App/Resource/*.cpp"
    "main/App/Resource/**/*.c"
    "main/App/Resource/**/*.cpp"
    "main/App/Utils/**.c"
    "main/App/Utils/**.cpp"
    "main/HAL/*.c"
    "main/HAL/*.cpp")
    # Compile the executable
    add_executable(${PROJECT_NAME} ${src_source})
    # link library
    target_link_libraries(${PROJECT_NAME} lvgl)
    target_link_libraries(${PROJECT_NAME} lv_drivers)
    target_link_libraries(${PROJECT_NAME} mingw32)
    target_link_libraries(${PROJECT_NAME} SDL2main)
    target_link_libraries(${PROJECT_NAME} SDL2)


    # Copy the SDL2.dll file to the build directory
    file(COPY SDL2.dll DESTINATION ../build)
    set(CPACK_PROJECT_NAME ${PROJECT_NAME})
    set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
    include(CPack)
else()
    message("${ESCAPE}[32mBuilding from external terminal - Generate hex file${ESCAPE}[0m")
    add_definitions(-DLV_MEM_CUSTOM=1)
    add_compile_definitions(CONFIG_IDF_TARGET_ESP32S3)
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    set(EXTRA_COMPONENT_DIRS lvgl)
    project(Tinybench)
    # Add external terminal-specific options here
endif()
