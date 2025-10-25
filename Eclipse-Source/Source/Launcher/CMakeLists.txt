cmake_minimum_required(VERSION 3.19.2)

# file(READ "${CMAKE_SOURCE_DIR}/Settings/EngineSettings.json" GAME_NAME_FILE)
# string(JSON GameJSONName GET "${GAME_NAME_FILE}" GameName)
set(GAME_NAME "Eclipsed Engine")

set(LAUNCHER_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE LAUNCHER_SOURCES
    "${LAUNCHER_ROOT}/main.cpp"
)

add_executable(Launcher "${LAUNCHER_ROOT}/main.cpp")

target_include_directories(Launcher PUBLIC ${OPENGL_SOURCES})
target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals)

# target_include_directories(ImGui PUBLIC ${IMGUI_SOURCES}/ImGui)
# target_include_directories(ImGui PUBLIC ${PLATFORMINTEGRATION_SOURCES})

target_link_libraries(Launcher PRIVATE -WHOLEARCHIVE:$<TARGET_FILE:Game>)

target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/)
target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Launcher/)

if(EDITOR)
    target_include_directories(Launcher PUBLIC ${CMAKE_SOURCE_DIR}/Source/Editor/)
    target_link_libraries(Launcher PUBLIC Editor)
endif()

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


target_link_libraries(Launcher PRIVATE Editor)
target_link_libraries(Launcher PRIVATE GraphicsEngine)
target_link_libraries(Launcher PRIVATE CoreEngine)
target_link_libraries(Launcher PRIVATE PhysicsEngine)
target_link_libraries(Launcher PRIVATE FMOD)

find_package(OpenGL REQUIRED)
target_link_libraries(Launcher PRIVATE OpenGL::GL)
target_link_libraries(Launcher PRIVATE Opengl)
target_link_libraries(Launcher PRIVATE ImGui)

set_target_properties(Launcher PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)