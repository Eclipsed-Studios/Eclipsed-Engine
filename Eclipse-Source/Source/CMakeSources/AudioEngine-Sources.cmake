set(AUDIO_ENGINE_ROOT "${CMAKE_SOURCE_DIR}/Source/Engine/EngineModules/AudioEngine")

file(GLOB_RECURSE AUDIO_ENGINE_SOURCES
    "${AUDIO_ENGINE_ROOT}/*.cpp"
    "${AUDIO_ENGINE_ROOT}/*.h"
    "${AUDIO_ENGINE_ROOT}/*.hpp"
    "${AUDIO_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
    )