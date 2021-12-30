cmake_minimum_required(VERSION 3.0.0)
project(balls VERSION 0.1.0)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SOURCES})

if(WIN32)
    target_link_libraries(
            balls PUBLIC
            "${PROJECT_SOURCE_DIR}/lib/libraylib.a"
            opengl32
            gdi32
            winmm
    )
else()
    target_link_libraries(
            balls PUBLIC
            raylib
            GL
            m
            pthread
            dl
            rt
            X11
    )
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
