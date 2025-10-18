cmake_minimum_required(VERSION 3.19.2)

set(UTILITIES_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Utilities")

file(GLOB_RECURSE UTILITIES_SOURCES
    "${UTILITIES_ROOT}/*.cpp"
    "${UTILITIES_ROOT}/*.h"
    "${UTILITIES_ROOT}/*.hpp"
    "${UTILITIES_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)

add_library(Utilities STATIC ${UTILITIES_SOURCES})

target_precompile_headers(Utilities PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

target_include_directories(Utilities PRIVATE "${UTILITIES_ROOT}")
target_include_directories(Utilities PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals)
target_include_directories(Utilities PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/rapidjson)

target_include_directories(Utilities PUBLIC ${DiscordSDK_SOURCES})
target_link_libraries(Utilities PUBLIC DiscordSDK)

foreach(source_file IN LISTS UTILITIES_SOURCES)
    file(RELATIVE_PATH source_path "${UTILITIES_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()