cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/NetworkEngine-Sources.cmake")


add_library(NetworkEngine STATIC ${NETWORK_ENGINE_SOURCES})
AddFilesToFolders("${NETWORK_ENGINE_SOURCES}" "${NETWORK_ENGINE_ROOT}")

target_precompile_headers(NetworkEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(NetworkEngine PROPERTIES FOLDER "Engine/EngineModules")

set_target_properties(NetworkEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libs"
)

# ---- EntityEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/EntityEngine-Sources.cmake")
target_include_directories(NetworkEngine PRIVATE ${ENTITY_ENGINE_ROOT})
target_link_libraries(NetworkEngine PRIVATE EntityEngine)

target_include_directories(NetworkEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source/Externals/asio")

set_target_properties(NetworkEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)