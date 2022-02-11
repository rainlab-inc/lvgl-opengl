cmake_minimum_required(VERSION 3.14)

project(lvgl-opengl)




#file(GLOB_RECURSE INCLUDES "lv_demos/*.h"  "lvgl/*.h"  "./*.h" )
#file(GLOB_RECURSE SOURCES  "lv_demos/*.c"  "lvgl/*.c" )

#add_executable(lvgl-opengl main.c sdl_gles.h sdl_gles.c gl.h gl.c ${SOURCES} ${INCLUDES})

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(lv_drivers/glad/include)
add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(lvgl-opengl main.c)

set(LV_CONF_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}
        CACHE STRING "" FORCE)


target_link_libraries(lvgl-opengl SDL2 lvgl::lvgl lv_drivers)
