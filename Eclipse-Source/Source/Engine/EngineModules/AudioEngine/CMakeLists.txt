cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AudioEngine-Sources.cmake")


add_library(AudioEngine STATIC ${AUDIO_ENGINE_SOURCES})
AddFilesToFolders("${AUDIO_ENGINE_SOURCES}" "${AUDIO_ENGINE_ROOT}")

target_precompile_headers(AudioEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(AudioEngine PROPERTIES FOLDER "Engine/EngineModules")

set_target_properties(AudioEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libs"
)

target_include_directories(AudioEngine PRIVATE ${AUDIO_ENGINE_ROOT})
target_include_directories(AudioEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})




# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(AudioEngine PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(AudioEngine PUBLIC AssetEngine)



target_include_directories(AudioEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/fmod)  # REMOVE WHEN AUDIO ENGINE IS ADDED
target_link_libraries(AudioEngine PRIVATE FMOD)


set_target_properties(AudioEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)