cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

project(Eclipsed-Engine LANGUAGES CXX)

add_compile_definitions(LEAN_AND_MEAN)


add_compile_definitions(
    ECLIPSED_EDITOR
    _ECLIPSED_EXPORT_DLL
    )

set_property(GLOBAL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")


# Declare cache variable with a default value if not set
if(NOT DEFINED EXE_OUTPUT_DIR OR EXE_OUTPUT_DIR STREQUAL "")
    set(EXE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Bin" CACHE PATH "Where to place executables" FORCE)
else()
    # Make sure it's in the cache without overwriting
    set(EXE_OUTPUT_DIR "${EXE_OUTPUT_DIR}" CACHE PATH "Where to place executables")
endif()

# set(EXE_OUTPUT_DIR "${EXE_OUTPUT_DIR}"
#     CACHE PATH "Where to place executables")

# if(NOT EXE_OUTPUT_DIR)
#     set(EXE_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/Bin" CACHE PATH "Where to place executables")
# endif()


# ---- Externals
add_subdirectory(Source/Externals/DiscordSDK)
add_subdirectory(Source/Externals/fmod)
add_subdirectory(Source/Externals/rapidjson)
add_subdirectory(Source/Externals/ImGui)
add_subdirectory(Source/Externals/OpenGL)
add_subdirectory(Source/Externals/SDL3)
add_subdirectory(Source/Externals/stb_image)
add_subdirectory(Source/Externals/Font-Awesome)



add_subdirectory(Source/Engine/Modules/CoreEngine)
add_subdirectory(Source/Engine/Modules/AssetEngine)
add_subdirectory(Source/Engine/Modules/AudioEngine)
add_subdirectory(Source/Engine/Modules/EntityEngine)
add_subdirectory(Source/Engine/Modules/GraphicsEngine)
add_subdirectory(Source/Engine/Modules/NetworkEngine)
add_subdirectory(Source/Engine/Modules/PhysicsEngine)

add_subdirectory(Source/Engine/EclipsedEngine)

add_subdirectory(Source/Launcher)









set_property(GLOBAL PROPERTY USE_FOLDERS ON)
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launcher) 


make_directory("${CMAKE_SOURCE_DIR}/Bin")

file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Assets/DLLs/*")
file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")

make_directory("${CMAKE_SOURCE_DIR}/Bin/Local")
file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Assets/Settings/*")
file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin/Local")

file(GLOB EngineAssets "${CMAKE_SOURCE_DIR}/Assets/EngineAssets")
file(COPY ${EngineAssets} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")



# if (MSVC)
#     add_compile_options(/FI ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
# else()
#     add_compile_options(-include ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
# endif()


# Move to launcher
# set_target_properties(Launcher PROPERTIES
#     VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
# )