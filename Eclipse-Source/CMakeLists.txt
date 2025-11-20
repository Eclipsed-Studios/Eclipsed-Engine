cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

project(Eclipsed-Engine LANGUAGES CXX)

add_compile_definitions(LEAN_AND_MEAN)


add_compile_definitions(ECLIPSED_EDITOR)

set_property(GLOBAL PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin")


# ---- Externals
add_subdirectory(Source/Externals/DiscordSDK)
add_subdirectory(Source/Externals/fmod)
add_subdirectory(Source/Externals/rapidjson)
add_subdirectory(Source/Externals/ImGui)
add_subdirectory(Source/Externals/OpenGL)
add_subdirectory(Source/Externals/SDL3)
add_subdirectory(Source/Externals/stb_image)
add_subdirectory(Source/Externals/Font-Awesome)

include_directories("${CMAKE_SOURCE_DIR}/Source/Externals")

# add_compile_definitions(ENGINE_SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/EngineSettings.json\")
# add_compile_definitions(GAME_SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/GameSettings.json\")
# add_compile_definitions(ENGINE_ASSETS_PATH=\"${CMAKE_SOURCE_DIR}/EngineAssets/\")
# add_compile_definitions(ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")
# add_compile_definitions(SOURCE_PATH=\"${CMAKE_SOURCE_DIR}/\")
# add_compile_definitions(SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/\")



# ---- Utilities
add_subdirectory(Source/Utilities)

include_directories("${CMAKE_SOURCE_DIR}/Source/Utilities")
link_libraries(Utilities)


# ---- Engines
add_subdirectory(Source/Engine/EngineModules/EntityEngine)
add_subdirectory(Source/Engine/EngineModules/AudioEngine)
add_subdirectory(Source/Engine/EngineModules/InputEngine)
add_subdirectory(Source/Engine/EngineModules/NetworkEngine)
add_subdirectory(Source/Engine/EngineModules/AssetEngine)
add_subdirectory(Source/Engine/EngineModules/GraphicsEngine)
add_subdirectory(Source/Engine/EngineModules/CoreEngine)
add_subdirectory(Source/Engine/EngineModules/PhysicsEngine)
add_subdirectory(Source/Engine/EclipsedEngine)
add_subdirectory(Source/Engine/EclipsedRuntime)



# ---- Launcher
add_subdirectory(Source/Launcher)






set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launcher) 


make_directory("${CMAKE_SOURCE_DIR}/Bin")
file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Tools/DLLs/*")
file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")



if (MSVC)
    add_compile_options(/FI ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
else()
    add_compile_options(-include ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
endif()


# Move to launcher
set_target_properties(Launcher PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)