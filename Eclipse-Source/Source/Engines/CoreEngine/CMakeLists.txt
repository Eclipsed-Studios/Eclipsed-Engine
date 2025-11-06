cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

set(CORE_ENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CoreEngine")
file(GLOB_RECURSE COREENGINE_SOURCES
    "${CORE_ENGINE_ROOT}/*.cpp"
    "${CORE_ENGINE_ROOT}/*.h"
    "${CORE_ENGINE_ROOT}/*.hpp"
    "${CORE_ENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)

add_library(CoreEngine STATIC ${COREENGINE_SOURCES})
AddFilesToFolders("${COREENGINE_SOURCES}" "${CORE_ENGINE_ROOT}")

target_precompile_headers(CoreEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(CoreEngine PROPERTIES FOLDER "Engines")



# ---- CoreEngine
target_include_directories(CoreEngine PRIVATE ${CORE_ENGINE_ROOT})
target_include_directories(CoreEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


# ---- InputEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/InputEngine-Sources.cmake")
target_include_directories(CoreEngine PUBLIC ${INPUT_ENGINE_ROOT})
target_link_libraries(CoreEngine PUBLIC InputEngine)


# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(CoreEngine PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(CoreEngine PUBLIC AssetEngine)


# ---- GraphicsEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/GraphicsEngine-Sources.cmake")
target_include_directories(CoreEngine PUBLIC ${GRAPHICS_ENGINE_ROOT})
target_link_libraries(CoreEngine PUBLIC GraphicsEngine)


# ---- Physics Engine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/PhysicsEngine-Sources.cmake")
target_include_directories(CoreEngine PUBLIC ${PHYSICS_ENGINE_ROOT})
target_link_libraries(CoreEngine PUBLIC PhysicsEngine)


# ---- EntityEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/EntityEngine-Sources.cmake")
target_include_directories(CoreEngine PUBLIC ${ENTITY_ENGINE_ROOT})
target_link_libraries(CoreEngine PUBLIC EntityEngine)


# ---- AudioEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AudioEngine-Sources.cmake")
target_include_directories(CoreEngine PUBLIC ${AUDIO_ENGINE_ROOT})
target_link_libraries(CoreEngine PUBLIC AudioEngine)


# ---- Externals
target_include_directories(CoreEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/stbi_image/) # REMOVE WHEN ASSET ENGINE IS ADDED

target_include_directories(CoreEngine PRIVATE ${PLATFORMINTEGRATION_SOURCES})

target_include_directories(CoreEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/fmod)  # REMOVE WHEN AUDIO ENGINE IS ADDED
target_link_libraries(CoreEngine PRIVATE FMOD)

set_target_properties(CoreEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)