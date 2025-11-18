cmake_minimum_required(VERSION 3.19.2)

set(IMGUI_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
file(GLOB_RECURSE IMGUI_SOURCES
    "${IMGUI_ROOT}/*.cpp"
    "${IMGUI_ROOT}/*.h"
    "${IMGUI_ROOT}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)



add_library(ImGui STATIC ${IMGUI_SOURCES})

set_target_properties(ImGui PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libs"
)

#target_precompile_headers(ImGui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(ImGui PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)

set_target_properties(ImGui PROPERTIES UNITY_BUILD OFF)
 
set_target_properties(ImGui PROPERTIES FOLDER "Externals")