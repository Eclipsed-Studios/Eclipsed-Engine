cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE IMGUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(ImGui STATIC ${IMGUI_SOURCES})
target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 
set_target_properties(ImGui PROPERTIES FOLDER "Externals")