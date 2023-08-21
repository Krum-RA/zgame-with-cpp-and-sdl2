cmake_minimum_required(VERSION 3.13)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDebug$<$<CONFIG:Debug>:Debug>")
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

add_subdirectory("thirdParty/SDL2")
add_subdirectory("thirdParty/SDL2_image")
add_subdirectory("thirdParty/SDL2_ttf")

project(main1)
set(CMAKE_CXX_STANDARD 17)

# Collect all source files for the main game
file(GLOB_RECURSE MAIN_GAME_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Create the main game executable and link all main game source files
add_executable(main1 "${MAIN_GAME_SOURCES}")

target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
target_include_directories(main1 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_link_libraries(main1 PRIVATE SDL2 SDL2_image SDL2_ttf)

if (WIN32)
    # Copy SDL2, SDL2_image, and SDL2_ttf DLL files to the output directory
    file(GLOB SDL_DLLS "${CMAKE_SOURCE_DIR}/thirdParty/SDL2/lib/x64/*.dll")
    file(GLOB SDL_IMAGE_DLLS "${CMAKE_SOURCE_DIR}/thirdParty/SDL2_image/lib/x64/*.dll")
    file(GLOB SDL_TTF_DLLS "${CMAKE_SOURCE_DIR}/thirdParty/SDL2_ttf/lib/x64/*.dll")

    set(ALL_DLLS ${SDL_DLLS} ${SDL_IMAGE_DLLS} ${SDL_TTF_DLLS})

    add_custom_command(TARGET main1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${ALL_DLLS}
            $<TARGET_FILE_DIR:main1>)
endif ()



# Find UnitTest++ library

##find_package(UnitTest++ REQUIRED)
##include_directories(${UTPP_INCLUDE_DIRS})

# Collect all source files for the tests, excluding main.cpp
#file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp")

# Collect all source files for the src folder, excluding main.cpp
#file(GLOB_RECURSE SRC_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
#set(EXCLUDED_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")

#list(APPEND FILTERED_SOURCES)
#foreach(source_file IN LISTS SRC_SOURCES)
#    if(NOT "${source_file}" STREQUAL "${EXCLUDED_SOURCE}")
#        list(APPEND FILTERED_SOURCES "${source_file}")
#    endif()
#endforeach()

#set(SRC_SOURCES ${FILTERED_SOURCES})

# Create the tests executable and link test source files and main game library
#add_executable(tests ${TEST_SOURCES} ${SRC_SOURCES})
#target_compile_definitions(tests PUBLIC RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/")
#target_include_directories(tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
#target_link_libraries(tests PRIVATE SDL2 SDL2_image SDL2_ttf UnitTest++)

#if (WIN32)
    # Copy SDL2, SDL2_image, and SDL2_ttf DLL files to the output directory
#    file(GLOB SDL_DLLS "${CMAKE_SOURCE_DIR}/thirdParty/SDL2/lib/x64/*.dll")
#    file(GLOB SDL_IMAGE_DLLS "${CMAKE_SOURCE_DIR}/thirdParty/SDL2_image/lib/x64/*.dll")
#    file(GLOB SDL_TTF_DLLS "${CMAKE_SOURCE_DIR}/thirdParty/SDL2_ttf/lib/x64/*.dll")

#    set(ALL_DLLS ${SDL_DLLS} ${SDL_IMAGE_DLLS} ${SDL_TTF_DLLS})

#    add_custom_command(TARGET tests POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#            ${ALL_DLLS}
#            $<TARGET_FILE_DIR:tests>)
#endif ()

#add_custom_target(run_tests COMMAND tests)