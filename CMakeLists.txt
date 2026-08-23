cmake_minimum_required(VERSION "4.0.0")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

option(ECLIPSED_EDITOR "If enabled, then builds the editor." ON)

add_compile_definitions(
    WIN32_LEAN_AND_MEAN
)

if(${ECLIPSED_EDITOR})
    include(CMake/generate/editor.cmake)
else()
    include(CMake/generate/game.cmake)
    message("The game is calling.")
endif()


project(Eclipsed-Engine LANGUAGES C CXX)

if(MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>" CACHE STRING "" FORCE)
endif()

option(ENABLE_DISCORD_SDK "Enables the discord sdk." ON)
if(${ENABLE_DISCORD_SDK})
    add_compile_definitions(ENABLE_DISCORD_SDK)
endif()


add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/fmod)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/cereal)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/FreeType)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/stb_image)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/rapidjson)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/box2d)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/asio)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/FontAwesome)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/ImGui)


add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Core)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Modules/Assets)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Modules/Audio)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Modules/Input)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Modules/ECS)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Modules/Renderer)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Modules/Physics)

add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Game)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/EclipsedEngine)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Launcher)


set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT Launcher
)