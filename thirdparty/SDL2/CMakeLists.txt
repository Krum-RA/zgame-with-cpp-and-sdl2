cmake_minimum_required(VERSION 3.13)
project(SDL2)

add_library(SDL2 INTERFACE)

# Set the path to the x64 directory containing the sdl2main.lib file
set(SDL2_X64_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/x64")

# Add the appropriate include directory
target_include_directories(SDL2 INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include/")

# Add the linker library for SDL2main
if (WIN32)
    target_link_libraries(SDL2 INTERFACE "${SDL2_X64_LIB_DIR}/SDL2main.lib")
    target_link_libraries(SDL2 INTERFACE "${SDL2_X64_LIB_DIR}/sdl2.lib")
endif ()
