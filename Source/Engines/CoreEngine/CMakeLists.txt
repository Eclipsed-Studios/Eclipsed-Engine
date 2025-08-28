cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE COREENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(CoreEngine STATIC ${COREENGINE_SOURCES})

target_compile_definitions(CoreEngine PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

target_include_directories(CoreEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

foreach(source_file IN LISTS COREENGINE_SOURCES)
    file(RELATIVE_PATH source_path "${CMAKE_CURRENT_SOURCE_DIR}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(source_group STREQUAL "")
        set(source_group "Root")
    endif()
    source_group("${source_group}" FILES "${source_file}")
endforeach()

set_target_properties(CoreEngine PROPERTIES FOLDER "Engines")