cmake_minimum_required(VERSION "3.19.2")

project(Zengine LANGUAGES CXX)

add_subdirectory(Source/Externals)
add_subdirectory(Source/Core)
add_subdirectory(Source/Editor)
add_subdirectory(Source/Game)


set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor) 