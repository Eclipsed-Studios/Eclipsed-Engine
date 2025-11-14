set(CORE_ENGINE_ROOT "${CMAKE_SOURCE_DIR}/Source/Engine/EngineModules/CoreEngine")

file(GLOB_RECURSE CORE_ENGINE_SOURCES
    "${CORE_ENGINE_ROOT}/*.cpp"
    "${CORE_ENGINE_ROOT}/*.h"
    "${CORE_ENGINE_ROOT}/*.hpp"
    "${CORE_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
    )