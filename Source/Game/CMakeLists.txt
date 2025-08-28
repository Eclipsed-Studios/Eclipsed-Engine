cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE GAME_SOURCES
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_executable(Game ${GAME_SOURCES})

target_compile_definitions(Game PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

set_target_properties(Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../Bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../Bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../Bin/"
)

target_link_libraries(Game PRIVATE Core)