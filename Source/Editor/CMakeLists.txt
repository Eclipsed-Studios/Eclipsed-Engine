cmake_minimum_required(VERSION 3.19.2)

file(READ "${CMAKE_SOURCE_DIR}/Settings/GameName.txt" GAME_NAME_FILE)

# Use a regex to capture the quoted name after [name]
string(REGEX MATCH "\\[name\\][ \t\r\n]*\"([^\"]+)\"" _match "${GAME_NAME_FILE}")

# The captured value is in CMAKE_MATCH_1
set(GAME_NAME "${CMAKE_MATCH_1}")

file(GLOB_RECURSE EDITOR_SOURCES
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_executable(Editor ${EDITOR_SOURCES})

set_target_properties(Editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/../Bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/../Bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/../Bin/"
    OUTPUT_NAME "${GAME_NAME}"


)

target_link_libraries(Editor PRIVATE Core)