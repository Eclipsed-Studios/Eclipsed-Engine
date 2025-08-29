find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

file(READ "${CMAKE_SOURCE_DIR}/Settings/GameSettings.json" GAME_NAME_FILE)
string(JSON GameJSONName GET "${GAME_NAME_FILE}" GameName)
set(GAME_NAME "${GameJSONName}")

file(GLOB_RECURSE EDITOR_SOURCES
    "*.cpp"
    "*.h"
    "*.hpp"
)

add_executable(Editor ${EDITOR_SOURCES})

target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals)

target_compile_definitions(Editor PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

set_target_properties(Editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin"
    OUTPUT_NAME "${GAME_NAME}"
)

target_link_libraries(Editor PRIVATE GraphicsEngine)
target_link_libraries(Editor PRIVATE CoreEngine)
target_link_libraries(Editor PRIVATE FMOD)
target_link_libraries(Editor PRIVATE OpenGL::GL)
target_link_libraries(Editor PRIVATE Opengl)
