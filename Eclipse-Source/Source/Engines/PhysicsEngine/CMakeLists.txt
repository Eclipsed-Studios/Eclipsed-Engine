cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

set(PHYSICS_ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/PhysicsEngine")

file(GLOB_RECURSE PHYSICS_ENGINE_SOURCES
    "${PHYSICS_ENGINE_ROOT}/*.cpp"
    "${PHYSICS_ENGINE_ROOT}/*.h"
    "${PHYSICS_ENGINE_ROOT}/*.hpp"
    "${PHYSICS_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
    )
    
add_library(PhysicsEngine STATIC ${PHYSICS_ENGINE_SOURCES})
AddFilesToFolders("${PHYSICS_ENGINE_SOURCES}" "${PHYSICS_ENGINE_ROOT}")

target_precompile_headers(PhysicsEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(PhysicsEngine PROPERTIES FOLDER "Engines")


# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(PhysicsEngine PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(PhysicsEngine PUBLIC AssetEngine)



# ---- Physics Engine
target_include_directories(PhysicsEngine PRIVATE ${PHYSICS_ENGINE_ROOT})
target_include_directories(PhysicsEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# ---- Box2D
target_link_directories(PhysicsEngine PUBLIC "${CMAKE_SOURCE_DIR}/Tools/Libs/box2d")
target_link_libraries(PhysicsEngine PUBLIC debug box2d-d)
target_link_libraries(PhysicsEngine PUBLIC optimized box2d)

set_target_properties(PhysicsEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
