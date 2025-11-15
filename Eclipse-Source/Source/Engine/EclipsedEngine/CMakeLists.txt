cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

set(ECLIPSED_ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/EclipsedEngine")
file(GLOB_RECURSE ECLIPSED_ENGINE_SOURCES
    "${ECLIPSED_ENGINE_ROOT}/*.cpp"
    "${ECLIPSED_ENGINE_ROOT}/*.h"
    "${ECLIPSED_ENGINE_ROOT}/*.hpp"
    "${ECLIPSED_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)

add_library(EclipsedEngine STATIC ${ECLIPSED_ENGINE_SOURCES})
AddFilesToFolders("${ECLIPSED_ENGINE_SOURCES}" "${ECLIPSED_ENGINE_ROOT}")


set_target_properties(EclipsedEngine PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY  "${CMAKE_BINARY_DIR}/Libs"
)


target_precompile_headers(EclipsedEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(EclipsedEngine PROPERTIES FOLDER "Engine")

target_include_directories(EclipsedEngine PRIVATE ${ECLIPSED_ENGINE_ROOT})
target_include_directories(EclipsedEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# ---- CoreEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/CoreEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${CORE_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC CoreEngine)


# ---- InputEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/InputEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${INPUT_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC InputEngine)


# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC AssetEngine)


# ---- GraphicsEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/GraphicsEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${GRAPHICS_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC GraphicsEngine)


# ---- Physics Engine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/PhysicsEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${PHYSICS_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC PhysicsEngine)


# ---- EntityEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/EntityEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${ENTITY_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC EntityEngine)


# ---- AudioEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AudioEngine-Sources.cmake")
target_include_directories(EclipsedEngine PUBLIC ${AUDIO_ENGINE_ROOT})
target_link_libraries(EclipsedEngine PUBLIC AudioEngine)




set_target_properties(EclipsedEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)