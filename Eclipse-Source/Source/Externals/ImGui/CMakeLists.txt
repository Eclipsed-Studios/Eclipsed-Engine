cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE IMGUI_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)



add_library(ImGui STATIC ${IMGUI_SOURCES})

#target_precompile_headers(ImGui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ImGui PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)

set_target_properties(ImGui PROPERTIES UNITY_BUILD OFF)
 
set_target_properties(ImGui PROPERTIES FOLDER "Externals")