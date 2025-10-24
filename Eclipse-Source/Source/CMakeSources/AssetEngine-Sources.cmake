    set(ASSET_ENGINE_ROOT "${CMAKE_SOURCE_DIR}/Source/Engines/AssetEngine")
file(GLOB_RECURSE ASSET_ENGINE_SOURCES
    "${ASSET_ENGINE_ROOT}/*.cpp"
    "${ASSET_ENGINE_ROOT}/*.h"
    "${ASSET_ENGINE_ROOT}/*.hpp"
    "${ASSET_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)