cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

project(Eclipse LANGUAGES CXX)



if(CMAKE_GENERATOR MATCHES "Visual Studio")
    set(CMAKE_CONFIGURATION_TYPES
    Editor_D Editor_R
    Game_D Game_R
    CACHE STRING "" FORCE
)
else()
    set(CMAKE_BUILD_TYPE Editor_D CACHE STRING "Active build type for IntelliSense" FORCE)
endif()

set(CMAKE_CXX_FLAGS_EDITOR_D "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")
set(CMAKE_C_FLAGS_EDITOR_D "${CMAKE_C_FLAGS_DEBUG} /Zi /Od")
set(CMAKE_EXE_LINKER_FLAGS_EDITOR_D "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
set(CMAKE_SHARED_LINKER_FLAGS_EDITOR_D "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG")

set(CMAKE_CXX_FLAGS_EDITOR_R "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
set(CMAKE_C_FLAGS_EDITOR_R "${CMAKE_C_FLAGS_RELEASE} /O2 /DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS_EDITOR_R "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS_EDITOR_R "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")



set(CMAKE_CXX_FLAGS_GAME_D "${CMAKE_CXX_FLAGS_DEBUG} /Zi /Od")
set(CMAKE_C_FLAGS_GAME_D "${CMAKE_C_FLAGS_DEBUG} /Zi /Od")
set(CMAKE_EXE_LINKER_FLAGS_GAME_D "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG")
set(CMAKE_SHARED_LINKER_FLAGS_GAME_D "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG")

set(CMAKE_CXX_FLAGS_GAME_R "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
set(CMAKE_C_FLAGS_GAME_R "${CMAKE_C_FLAGS_RELEASE} /O2 /DNDEBUG")
set(CMAKE_EXE_LINKER_FLAGS_GAME_R "${CMAKE_EXE_LINKER_FLAGS_RELEASE}")
set(CMAKE_SHARED_LINKER_FLAGS_GAME_R "${CMAKE_SHARED_LINKER_FLAGS_RELEASE}")





add_compile_definitions(ENGINE_SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/GameSettings.json\")
add_compile_definitions(ENGINE_ASSETS_PATH=\"${CMAKE_SOURCE_DIR}/EngineAssets/\")
add_compile_definitions(ASSET_PATH=\"${CMAKE_SOURCE_DIR}/Assets/\")
add_compile_definitions(SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/\")

add_subdirectory(Source/Externals/DiscordSDK)
add_subdirectory(Source/Externals/fmod)
add_subdirectory(Source/Externals/rapidjson)
add_subdirectory(Source/Externals/ImGui)
add_subdirectory(Source/Externals/OpenGL)
add_subdirectory(Source/Externals/SDL3)
add_subdirectory(Source/Externals/stb_image)

add_subdirectory(Source/Utilities)

add_subdirectory(Source/Engines/GraphicsEngine)
add_subdirectory(Source/Engines/CoreEngine)
add_subdirectory(Source/Engines/PhysicsEngine)

add_subdirectory(Source/Game)

add_subdirectory(Source/Editor)
add_subdirectory(Source/Launcher)


foreach(target Editor Launcher CoreEngine GraphicsEngine PhysicsEngine Game Utilities)
    target_compile_definitions(${target} PRIVATE
        $<$<CONFIG:Editor_D>:_EDITOR>
        $<$<CONFIG:Editor_R>:_EDITOR>
        $<$<CONFIG:Game_D>:_GAME>
        $<$<CONFIG:Game_R>:_GAME>
    )
endforeach()


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor) 

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