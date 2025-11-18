set(PHYSICS_ENGINE_ROOT "${CMAKE_SOURCE_DIR}/Source/Engine/EngineModules/PhysicsEngine")

file(GLOB_RECURSE PHYSICS_ENGINE_SOURCES
    "${PHYSICS_ENGINE_ROOT}/*.cpp"
    "${PHYSICS_ENGINE_ROOT}/*.h"
    "${PHYSICS_ENGINE_ROOT}/*.hpp"
    "${PHYSICS_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
    )