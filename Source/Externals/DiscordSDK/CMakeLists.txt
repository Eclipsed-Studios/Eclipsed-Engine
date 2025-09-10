cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE DiscordSDK_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)

add_library(DiscordSDK STATIC ${DiscordSDK_SOURCES})

target_precompile_headers(DiscordSDK PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

target_include_directories(DiscordSDK PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(DiscordSDK PUBLIC "${CMAKE_SOURCE_DIR}/Tools/Libs/discord_sdk")
target_link_libraries(DiscordSDK PRIVATE "discord_game_sdk")

set_target_properties(DiscordSDK PROPERTIES FOLDER "Externals")
set_target_properties(DiscordSDK PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 20)