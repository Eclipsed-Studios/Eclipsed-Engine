cmake_minimum_required(VERSION 3.19.2)

set(PHYSENGINE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE PHYSENGINE_SOURCES
    "${PHYSENGINE_ROOT}/*.cpp"
    "${PHYSENGINE_ROOT}/*.h"
    "${PHYSENGINE_ROOT}/*.hpp"
    "${PHYSENGINE_ROOT}/*.inl"
)

add_library(PhysicsEngine STATIC ${PHYSENGINE_SOURCES})

target_include_directories(PhysicsEngine PUBLIC ${CMAKE_SOURCE_DIR}/Source/Externals/)

target_link_directories(PhysicsEngine PUBLIC "${CMAKE_SOURCE_DIR}/Tools/Libs/box2d")
target_link_libraries(PhysicsEngine PUBLIC debug box2d-d)
target_link_libraries(PhysicsEngine PUBLIC optimized box2d)

target_include_directories(PhysicsEngine PUBLIC "${PHYSENGINE_ROOT}")

foreach(source_file IN LISTS PHYSENGINE_SOURCES)
    file(RELATIVE_PATH source_path "${PHYSENGINE_ROOT}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(NOT source_group STREQUAL "")
        source_group("${source_group}" FILES "${source_file}")
    else()
        source_group("" FILES "${source_file}")
    endif()
endforeach()

set_target_properties(PhysicsEngine PROPERTIES FOLDER "Engines")