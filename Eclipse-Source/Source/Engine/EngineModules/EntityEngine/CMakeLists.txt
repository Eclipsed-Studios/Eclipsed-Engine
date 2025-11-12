cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/EntityEngine-Sources.cmake")

add_library(EntityEngine STATIC ${ENTITY_ENGINE_SOURCES})
AddFilesToFolders("${ENTITY_ENGINE_SOURCES}" "${ENTITY_ENGINE_ROOT}")

target_precompile_headers(EntityEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(EntityEngine PROPERTIES FOLDER "Engine/EngineModules")

set_target_properties(EntityEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libs"
)

target_include_directories(EntityEngine PRIVATE ${ENTITY_ENGINE_ROOT})
target_include_directories(EntityEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})



# ---- InputEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/InputEngine-Sources.cmake")
target_include_directories(EntityEngine PUBLIC ${INPUT_ENGINE_ROOT})
target_link_libraries(EntityEngine PUBLIC InputEngine)



# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(EntityEngine PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(EntityEngine PUBLIC AssetEngine)


# ---- GraphicsEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/GraphicsEngine-Sources.cmake")
target_include_directories(EntityEngine PUBLIC ${GRAPHICS_ENGINE_ROOT})
target_link_libraries(EntityEngine PUBLIC GraphicsEngine)


# ---- Physics Engine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/PhysicsEngine-Sources.cmake")
target_include_directories(EntityEngine PUBLIC ${PHYSICS_ENGINE_ROOT})
target_link_libraries(EntityEngine PUBLIC PhysicsEngine)


# ---- Externals
target_include_directories(EntityEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/stbi_image/) # REMOVE WHEN ASSET ENGINE IS ADDED

target_include_directories(EntityEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/fmod)  # REMOVE WHEN AUDIO ENGINE IS ADDED
target_link_libraries(EntityEngine PRIVATE FMOD)

target_include_directories(EntityEngine PRIVATE ${PLATFORMINTEGRATION_SOURCES})



set_target_properties(EntityEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)