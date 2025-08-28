find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE CORE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/*.hpp"
)

add_library(Core STATIC ${CORE_SOURCES})

# Include Directories
target_include_directories(Core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Externals PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Linking library
target_link_libraries(Core PUBLIC Externals)




# Organize files in filters by folder
foreach(source_file IN LISTS CORE_SOURCES)
    file(RELATIVE_PATH source_path "${CMAKE_CURRENT_SOURCE_DIR}" "${source_file}")
    get_filename_component(source_group "${source_path}" PATH)
    if(source_group STREQUAL "")
        set(source_group "Root")
    endif()
    source_group("${source_group}" FILES "${source_file}")
endforeach()

