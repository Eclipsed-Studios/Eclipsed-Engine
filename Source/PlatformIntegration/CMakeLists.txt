cmake_minimum_required(VERSION 3.19.2)

set(PLATFORMINTEGRATION_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/PlatformIntegration")

file(GLOB_RECURSE PLATFORMINTEGRATION_SOURCES
    "${PLATFORMINTEGRATION_ROOT}/*.cpp"
    "${PLATFORMINTEGRATION_ROOT}/*.h"
    "${PLATFORMINTEGRATION_ROOT}/*.hpp"
    "${PLATFORMINTEGRATION_ROOT}/*.inl"
)

add_library(PlatformIntegration STATIC ${PLATFORMINTEGRATION_SOURCES})

target_include_directories(PlatformIntegration PUBLIC "${PLATFORMINTEGRATION_ROOT}")

foreach(source_file IN LISTS PLATFORMINTEGRATION_SOURCES)
    file(RELATIVE_PATH source_path "${PLATFORMINTEGRATION_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()


target_include_directories(PlatformIntegration PUBLIC ${DiscordSDK_SOURCES})
target_link_libraries(PlatformIntegration PRIVATE DiscordSDK)

set_target_properties(PlatformIntegration PROPERTIES FOLDER "Utilils")