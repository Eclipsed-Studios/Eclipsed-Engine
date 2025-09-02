cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

set(GAME_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Game")

file(GLOB_RECURSE GAME_SOURCES
    "${GAME_ROOT}/*.cpp"
    "${GAME_ROOT}/*.h"
    "${GAME_ROOT}/*.hpp"
    "${GAME_ROOT}/*.inl"
)

add_library(Game STATIC ${GAME_SOURCES})

target_compile_definitions(Game PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

target_include_directories(Game PUBLIC ${GAME_ROOT})
target_include_directories(Game PUBLIC ${CMAKE_SOURCE_DIR}/Source/Utilities/Utilities/)
target_include_directories(Game PUBLIC ${COREENGINE_ROOT})

target_link_libraries(Game PUBLIC PhysicsEngine)
target_link_libraries(Game PUBLIC CoreEngine)

foreach(source_file IN LISTS GAME_SOURCES)
    file(RELATIVE_PATH source_path "${GAME_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()