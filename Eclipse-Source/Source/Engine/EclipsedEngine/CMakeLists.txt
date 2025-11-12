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

target_precompile_headers(EclipsedEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(EclipsedEngine PROPERTIES FOLDER "Engine")



set_target_properties(EclipsedEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)