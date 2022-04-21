cmake_minimum_required(VERSION 3.14)

project(lvgl-opengl)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(lv_drivers/glad/include)

add_compile_definitions(LV_CONF_INCLUDE_SIMPLE)

add_subdirectory(glad)
add_subdirectory(lvgl)
add_subdirectory(lv_drivers)

add_executable(lvgl-opengl main.c)

set(LV_CONF_PATH
        ${CMAKE_CURRENT_SOURCE_DIR}
        CACHE STRING "" FORCE)


target_link_libraries(lvgl glad)
target_link_libraries(lv_drivers glad)

target_link_libraries(lvgl-opengl SDL2 lvgl::lvgl lvgl::examples lvgl::demos lv_drivers)
