cmake_minimum_required(VERSION "4.0.0")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

option(BUILD_EDITOR "If enabled, then builds the editor." ON)

add_compile_definitions(
    WIN32_LEAN_AND_MEAN
)

if(BUILD_EDITOR)
    include(CMake/generate/editor.cmake)
else()
    include(CMake/generate/game.cmake)
endif()

project(${PROJ_NAME} LANGUAGES C CXX)

option(ENABLE_NETWORKING "Includes the network engine in game build." ON)
if(${ENABLE_NETWORKING})
    add_compile_definitions(ECLIPSED_NETWORKING)
endif()

option(ENABLE_STEAM_SDK "Enables the steam sdk." ON)
if(${ENABLE_STEAM_SDK})
    add_compile_definitions(ENABLE_STEAM_SDK)
endif()

option(ENABLE_DISCORD_SDK "Enables the discord sdk." ON)
if(${ENABLE_DISCORD_SDK})
    add_compile_definitions(ENABLE_DISCORD_SDK)
endif()

add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/fmod)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/cereal)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/FreeType)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/stb_image)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/rapidjson)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/box2d)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/asio)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/FontAwesome)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/ImGui)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Source/Externals/steamsdk/CMakeLists.txt")
    add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Externals/steamsdk)
    add_compile_definitions(STEAMSDK_PRESENT)
endif()









add_subdirectory(${CMAKE_SOURCE_DIR}/Source/EclipsedEngine)
add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Editor)

add_subdirectory(${CMAKE_SOURCE_DIR}/Source/Launcher)


file(GLOB SUBDIRS LIST_DIRECTORIES true
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/Plugins/*"
)

foreach(DIR ${SUBDIRS})
    if(IS_DIRECTORY "${DIR}")
        get_filename_component(DIR_NAME "${DIR}" NAME)

        add_subdirectory("${DIR}")
  
        add_dependencies(Launcher ${DIR_NAME})
        add_dependencies(Editor ${DIR_NAME})
    endif()
endforeach()


set_property(TARGET OpenGL_Renderer
    PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL"
)

set_property(TARGET EclipsedEngine
    PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDebugDLL"
)

set_property(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    PROPERTY VS_STARTUP_PROJECT Launcher
)


# set_property(GLOBAL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")


# set(LAUNCH_ARGS "--defaultArg" CACHE STRING "Arguments to pass to launcher")

# set(BUILD_GAME_PATH "${CMAKE_SOURCE_DIR}/Bin" CACHE PATH "Game build path")
# set(CONFIG "Debug" CACHE STRING "Game build path")

# # Declare cache variable with a default value if not set
# if(NOT DEFINED EXE_OUTPUT_DIR OR EXE_OUTPUT_DIR STREQUAL "")
#     set(EXE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Bin" CACHE PATH "Where to place executables" FORCE)
# else()
#     # Make sure it's in the cache without overwriting
#     set(EXE_OUTPUT_DIR "${EXE_OUTPUT_DIR}" CACHE PATH "Where to place executables")
# endif()

# # set(EXE_OUTPUT_DIR "${EXE_OUTPUT_DIR}"
# #     CACHE PATH "Where to place executables")

# # if(NOT EXE_OUTPUT_DIR)
# #     set(EXE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Bin" CACHE PATH "Where to place executables")
# # endif()


# add_compile_definitions(BEGIN_IMPL=//)
# add_compile_definitions(END_IMPL=//)


# # ---- Externals
# if(${ENABLE_DISCORD_SDK})
#     add_subdirectory(Source/Externals/DiscordSDK)
# endif()

# add_subdirectory(Source/Externals/fmod)
# add_subdirectory(Source/Externals/rapidjson)
# add_subdirectory(Source/Externals/ImGui)
# add_subdirectory(Source/Externals/OpenGL)
# add_subdirectory(Source/Externals/SDL3)
# add_subdirectory(Source/Externals/stb_image)
# add_subdirectory(Source/Externals/Font-Awesome)



# add_subdirectory(Source/Engine/Modules/Core)
# add_subdirectory(Source/Engine/Modules/Assets)
# add_subdirectory(Source/Engine/Modules/AudioEngine)
# add_subdirectory(Source/Engine/Modules/EntityEngine)
# add_subdirectory(Source/Engine/Modules/Renderer)

# if(${ENABLE_NETWORKING})
#     add_subdirectory(Source/Engine/Modules/Networking)
# endif()

# add_subdirectory(Source/Engine/Modules/PhysicsEngine)

# add_subdirectory(Source/Engine/EclipsedEngine)

# add_subdirectory(Source/Launcher)
# if(ECL_EDITOR)
#     add_subdirectory(Source/Hub)
# endif()

# if(INCLUDE_GAME)
#     add_subdirectory(${BUILD_GAME_PATH}  ${BUILD_GAME_PATH}/Library/Game-Building-Binary/Game-Proj)
# endif()

# message(${CMAKE_SOURCE_DIR})

# # add_custom_target(post_build
# #     COMMAND python ${CMAKE_SOURCE_DIR}/Tools/Build/export-headers.py
# #             --config $<CONFIG>
# #             --input "${CMAKE_SOURCE_DIR}/Source/Engine"
# #             --output "${CMAKE_SOURCE_DIR}/Bin/Headers"
# #     COMMENT "Running post-build script"
# #     DEPENDS EclipsedEngine Launcher
# # )





# set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launcher)

# make_directory("${CMAKE_SOURCE_DIR}/Bin")

# file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Assets/DLLs/*")
# file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")

# make_directory("${CMAKE_SOURCE_DIR}/Bin/Local")
# file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Assets/Settings/*")
# file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin/Local")

# file(GLOB EngineAssets "${CMAKE_SOURCE_DIR}/Assets/EngineAssets")
# file(COPY ${EngineAssets} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")

