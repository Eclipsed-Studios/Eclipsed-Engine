cmake_minimum_required(VERSION 3.19.2)

set(COREENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CoreEngine")

file(GLOB_RECURSE COREENGINE_SOURCES
    "${COREENGINE_ROOT}/*.cpp"
    "${COREENGINE_ROOT}/*.h"
    "${COREENGINE_ROOT}/*.hpp"
    "${COREENGINE_ROOT}/*.inl"
)

add_library(CoreEngine STATIC ${COREENGINE_SOURCES})

target_compile_definitions(CoreEngine PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

target_include_directories(CoreEngine PUBLIC ${COREENGINE_ROOT})
target_include_directories(CoreEngine PUBLIC ${GRAPHICSENGINE_SOURCES})

target_include_directories(CoreEngine PUBLIC ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/)

target_include_directories(CoreEngine PUBLIC ${PLATFORMINTEGRATION_SOURCES})

target_link_libraries(CoreEngine PRIVATE GraphicsEngine)

foreach(source_file IN LISTS COREENGINE_SOURCES)
    file(RELATIVE_PATH source_path "${COREENGINE_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()

set_target_properties(CoreEngine PROPERTIES FOLDER "Engines")


target_link_libraries(CoreEngine PRIVATE PlatformIntegration)