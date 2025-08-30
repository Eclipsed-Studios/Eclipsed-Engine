find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

file(READ "${CMAKE_SOURCE_DIR}/Settings/GameSettings.json" GAME_NAME_FILE)
string(JSON GameJSONName GET "${GAME_NAME_FILE}" GameName)
set(GAME_NAME "${GameJSONName}")

set(EDITOR_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/Editor")

file(GLOB_RECURSE EDITOR_SOURCES
    "${EDITOR_ROOT}/*.cpp"
    "${EDITOR_ROOT}/*.h"
    "${EDITOR_ROOT}/*.hpp"
    "${EDITOR_ROOT}/*.inl"
)



add_executable(Editor ${EDITOR_SOURCES})

target_include_directories(Editor PUBLIC ${OPENGL_SOURCES})
target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals)
target_include_directories(ImGui PUBLIC ${IMGUI_SOURCES}/ImGui)



target_include_directories(Editor PUBLIC ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/)

target_compile_definitions(Editor PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

set_target_properties(Editor PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin"
RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin"
OUTPUT_NAME "${GAME_NAME}"
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
target_link_libraries(Editor PRIVATE FMOD)
target_link_libraries(Editor PRIVATE OpenGL::GL)
target_link_libraries(Editor PRIVATE Opengl)
target_link_libraries(Editor PRIVATE ImGui)