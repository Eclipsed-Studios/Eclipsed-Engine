set(INPUT_ENGINE_ROOT "${CMAKE_SOURCE_DIR}/Source/Engine/EngineModules/InputEngine")

file(GLOB_RECURSE INPUT_ENGINE_SOURCES
    "${INPUT_ENGINE_ROOT}/*.cpp"
    "${INPUT_ENGINE_ROOT}/*.h"
    "${INPUT_ENGINE_ROOT}/*.hpp"
    "${INPUT_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
    )