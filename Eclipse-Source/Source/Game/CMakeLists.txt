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

target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine)
target_link_libraries(Game PRIVATE CoreEngine)

target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/Source/Engines/GraphicsEngine)
target_link_libraries(Game PRIVATE GraphicsEngine)

target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/Source/Engines/PhysicsEngine)
target_link_libraries(Game PRIVATE PhysicsEngine)

target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals) 
target_include_directories(Game PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/fmod)  # REMOVE WHEN AUDIO ENGINE IS ADDED
target_link_libraries(Game PRIVATE FMOD)

target_include_directories(Game PUBLIC ${GAME_ROOT})


foreach(source_file IN LISTS GAME_SOURCES)
    file(RELATIVE_PATH source_path "${GAME_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()

set_target_properties(Game PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)