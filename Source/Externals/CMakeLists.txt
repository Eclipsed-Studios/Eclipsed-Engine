cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE EXTERNAL_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(Externals STATIC ${EXTERNAL_SOURCES})
target_include_directories(Externals PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
 
target_link_libraries(Externals PUBLIC
    "${CMAKE_SOURCE_DIR}/Tools/Libs/discord_sdk/discord_game_sdk.dll.lib"
    
    "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fsbank_vc.lib"
    optimized "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmod_vc.lib"
    optimized "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmodstudio_vc.lib"

    debug "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmodL_vc.lib"
    debug "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmodstudioL_vc.lib"
)