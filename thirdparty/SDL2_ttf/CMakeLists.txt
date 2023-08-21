cmake_minimum_required(VERSION 3.13)
project(SDL2_ttf)


add_library(SDL2_ttf INTERFACE)

set(SDL2_X64_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/x64")

target_include_directories(SDL2_ttf INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

if (WIN32)
    target_link_libraries(SDL2_ttf INTERFACE "${SDL2_X64_LIB_DIR}/sdl2_ttf.lib")
endif ()