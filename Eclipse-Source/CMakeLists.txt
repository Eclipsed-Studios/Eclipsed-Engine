cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

project(Eclipse LANGUAGES CXX)




add_compile_definitions(ENGINE_SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/EngineSettings.json\")
add_compile_definitions(GAME_SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/GameSettings.json\")
add_compile_definitions(ENGINE_ASSETS_PATH=\"${CMAKE_SOURCE_DIR}/EngineAssets/\")
add_compile_definitions(ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")
add_compile_definitions(SOURCE_PATH=\"${CMAKE_SOURCE_DIR}/\")
add_compile_definitions(SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/\")

get_filename_component(PARENT_DIR "${CMAKE_SOURCE_DIR}" DIRECTORY)

# Define SOURCE_PATH as a compile definition
add_compile_definitions(SOURCE=\"${PARENT_DIR}/\")

add_subdirectory(Source/Externals/DiscordSDK)
add_subdirectory(Source/Externals/fmod)
add_subdirectory(Source/Externals/rapidjson)
add_subdirectory(Source/Externals/ImGui)
add_subdirectory(Source/Externals/OpenGL)
add_subdirectory(Source/Externals/SDL3)
add_subdirectory(Source/Externals/stb_image)
add_subdirectory(Source/Externals/Font-Awesome)

add_subdirectory(Source/Utilities)

add_subdirectory(Source/Engines/GraphicsEngine)
add_subdirectory(Source/Engines/CoreEngine)
add_subdirectory(Source/Engines/PhysicsEngine)

add_subdirectory(Source/Game)

add_subdirectory(Source/Editor)
add_subdirectory(Source/Launcher)

foreach(target Editor Launcher CoreEngine GraphicsEngine PhysicsEngine Game Utilities)
    target_compile_definitions(${target} PRIVATE
        $<$<CONFIG:Debug>:_EDITOR>
        $<$<CONFIG:Release>:_GAME>
    )

    if (MSVC)
        target_compile_options(${target} PRIVATE /FI ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
    else()
        target_compile_options(${target} PRIVATE -include ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
    endif()
endforeach()

if (MSVC)
        target_compile_options(CoreEngine PRIVATE /FI ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
        target_compile_options(Game PRIVATE /FI ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
    else()
        target_compile_options(CoreEngine PRIVATE -include ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
        target_compile_options(Game PRIVATE -include ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
    endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launcher) 

set_target_properties(Editor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)

set_target_properties(Launcher PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)

make_directory("${CMAKE_SOURCE_DIR}/Bin")
file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Tools/DLLs/*")
file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")

add_compile_definitions(LEAN_AND_MEAN)


include_directories("${CMAKE_SOURCE_DIR}/Source/Utilities")

target_link_libraries(CoreEngine PRIVATE Utilities)
target_link_libraries(GraphicsEngine PRIVATE Utilities)
target_link_libraries(Editor PRIVATE Utilities)
target_link_libraries(Launcher PRIVATE Utilities)
target_link_libraries(PhysicsEngine PRIVATE Utilities)
target_link_libraries(Game PRIVATE Utilities)

set_target_properties(CoreEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(GraphicsEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Editor PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Launcher PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(PhysicsEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Game PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Utilities PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)