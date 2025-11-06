find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)


set(EDITOR_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Editor")

file(GLOB_RECURSE EDITOR_SOURCES
    "${EDITOR_ROOT}/*.cpp"
    "${EDITOR_ROOT}/*.h"
    "${EDITOR_ROOT}/*.hpp"
    "${EDITOR_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h" 
)

add_library(Editor STATIC ${EDITOR_SOURCES})
# add_executable(Editor ${EDITOR_SOURCES})

target_precompile_headers(Editor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

target_include_directories(Editor PUBLIC ${OPENGL_SOURCES})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals)

if(MSVC) # Box2D specific warning. 
    target_link_options(Editor PRIVATE "/ignore:4098")
    target_link_options(Editor PRIVATE "/ignore:4099")
endif()

target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/)
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Editor/)
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Editor/Editor)

set_target_properties(Editor PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin"
RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin"
)

foreach(source_file IN LISTS EDITOR_SOURCES)
    file(RELATIVE_PATH source_path "${EDITOR_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()


target_link_libraries(Editor PRIVATE GraphicsEngine)
target_link_libraries(Editor PRIVATE CoreEngine)
target_link_libraries(Editor PRIVATE PhysicsEngine)
target_link_libraries(Editor PRIVATE FMOD)
target_link_libraries(Editor PRIVATE OpenGL::GL)
target_link_libraries(Editor PRIVATE Opengl)
target_link_libraries(Editor PRIVATE ImGui)

set_target_properties(Editor PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
