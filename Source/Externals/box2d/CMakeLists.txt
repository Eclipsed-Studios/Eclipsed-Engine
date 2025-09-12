cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE box2d_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)


add_library(box2d INTERFACE)
target_include_directories(box2d INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(box2d INTERFACE "${CMAKE_SOURCE_DIR}/Tools/Libs/box2d")

target_link_libraries(box2d INTERFACE
    debug box2d-d
    optimized box2d
)

set_target_properties(box2d PROPERTIES FOLDER "Externals")
set_target_properties(box2d PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 20)