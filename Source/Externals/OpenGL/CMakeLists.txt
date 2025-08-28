cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE OPENGL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(OpenGL INTERFACE)
target_include_directories(OpenGL INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(FMOD INTERFACE
    "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/glfw3.lib"
    "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/glfw3_mt.lib"
)

set_target_properties(OpenGL PROPERTIES FOLDER "Externals")