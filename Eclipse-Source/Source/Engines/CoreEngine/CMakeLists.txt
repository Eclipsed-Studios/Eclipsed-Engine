cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

set(COREENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/CoreEngine")
file(GLOB_RECURSE COREENGINE_SOURCES
    "${COREENGINE_ROOT}/*.cpp"
    "${COREENGINE_ROOT}/*.h"
    "${COREENGINE_ROOT}/*.hpp"
    "${COREENGINE_ROOT}/*.inl"
    "${CMAKE_CURRENT_SOURCE_DIR}/pch.h"
)

add_library(CoreEngine STATIC ${COREENGINE_SOURCES})

target_precompile_headers(CoreEngine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(CoreEngine PROPERTIES FOLDER "Engines")


# ---- CoreEngine
target_include_directories(CoreEngine PRIVATE ${COREENGINE_ROOT})

# ---- GraphicsEngine
target_include_directories(CoreEngine PRIVATE ${GRAPHICSENGINE_ROOT})
target_link_libraries(CoreEngine PRIVATE GraphicsEngine)


# ---- Physics Engine
target_include_directories(CoreEngine PRIVATE ${PHYSICSENGINE_ROOT})
target_link_libraries(CoreEngine PRIVATE PhysicsEngine)


# ---- Externals
target_include_directories(CoreEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/stbi_image/) # REMOVE WHEN ASSET ENGINE IS ADDED

target_include_directories(CoreEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/fmod)
target_link_libraries(CoreEngine PRIVATE FMOD)

target_include_directories(CoreEngine PRIVATE ${PLATFORMINTEGRATION_SOURCES})

foreach(source_file IN LISTS COREENGINE_SOURCES)
    file(RELATIVE_PATH source_path "${COREENGINE_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()