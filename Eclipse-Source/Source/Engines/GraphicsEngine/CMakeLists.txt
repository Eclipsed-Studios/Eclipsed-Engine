find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE GRAPHICSENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(GraphicsEngine STATIC ${GRAPHICSENGINE_SOURCES})

target_precompile_headers(GraphicsEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

target_compile_definitions(GraphicsEngine PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

# Include Directories
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
target_include_directories(GraphicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals)

target_link_libraries(GraphicsEngine PRIVATE OpenGL::GL)
target_link_libraries(GraphicsEngine PRIVATE Opengl)

# Organize files in filters by folder
foreach(source_file IN LISTS GRAPHICSENGINE_SOURCES)
    file(RELATIVE_PATH source_path "${CMAKE_CURRENT_SOURCE_DIR}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(source_group STREQUAL "")
        set(source_group "Root")
    endif()
    source_group("${source_group}" FILES "${source_file}")
endforeach()

set_target_properties(GraphicsEngine PROPERTIES FOLDER "Engines")