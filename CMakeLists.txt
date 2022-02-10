cmake_minimum_required(VERSION 3.14)

project(lvgl-opengl)

add_subdirectory(glad)



file(GLOB_RECURSE INCLUDES "lv_demos/*.h"  "lvgl/*.h"  "./*.h" )
file(GLOB_RECURSE SOURCES  "lv_demos/*.c"  "lvgl/*.c" )

add_executable(lvgl-opengl main.c sdl_gles.h sdl_gles.c gl.h gl.c ${SOURCES} ${INCLUDES})

set(LV_CONF_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}
        CACHE STRING "" FORCE)


target_link_libraries(lvgl-opengl glad SDL2)
