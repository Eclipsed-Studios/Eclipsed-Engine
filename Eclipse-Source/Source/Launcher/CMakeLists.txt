cmake_minimum_required(VERSION 3.19.2)

file(READ "${CMAKE_SOURCE_DIR}/Settings/EngineSettings.json" GAME_NAME_FILE)
string(JSON GameJSONName GET "${GAME_NAME_FILE}" GameName)
set(GAME_NAME "${GameJSONName}")

set(LAUNCHER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE LAUNCHER_SOURCES
    "${LAUNCHER_ROOT}/main.cpp"
)

add_executable(Launcher "${LAUNCHER_ROOT}/main.cpp")

message(STATUS "Game Name: ${GAME_NAME}")

target_include_directories(Launcher PUBLIC ${OPENGL_SOURCES})
target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals)

# target_include_directories(ImGui PUBLIC ${IMGUI_SOURCES}/ImGui)
# target_include_directories(ImGui PUBLIC ${PLATFORMINTEGRATION_SOURCES})



target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/)
target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Launcher/)
target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Editor/)

target_compile_definitions(Launcher PRIVATE ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")

set_target_properties(Launcher PROPERTIES
RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin"
RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin"
OUTPUT_NAME "${GAME_NAME}_$<CONFIG>"
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")

foreach(source_file IN LISTS LAUNCHER_SOURCES)
    file(RELATIVE_PATH source_path "${LAUNCHER_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()


target_link_libraries(Launcher PRIVATE GraphicsEngine)
target_link_libraries(Launcher PRIVATE CoreEngine)
target_link_libraries(Launcher PRIVATE PhysicsEngine)
target_link_libraries(Launcher PRIVATE FMOD)
target_link_libraries(Launcher PRIVATE Editor)
find_package(OpenGL REQUIRED)
target_link_libraries(Launcher PRIVATE OpenGL::GL)
target_link_libraries(Launcher PRIVATE Opengl)
target_link_libraries(Launcher PRIVATE ImGui)