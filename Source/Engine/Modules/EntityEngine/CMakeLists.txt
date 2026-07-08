# include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

# cmake_minimum_required(VERSION 3.19.2)

# get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# set(ROOT "${CMAKE_CURRENT_SOURCE_DIR}/${CURRENT_DIR_NAME}")
# file(GLOB_RECURSE SOURCES
#     "${ROOT}/*.cpp"
#     "${ROOT}/*.c"
#     "${ROOT}/*.h"
#     "${ROOT}/*.hpp"
#     "${ROOT}/*.inl"
# )


# set(${CURRENT_DIR_NAME}_Include ${SOURCES})

# add_library(${CURRENT_DIR_NAME} ${TYPE})


# target_sources(${CURRENT_DIR_NAME} PRIVATE ${SOURCES})
# target_sources(${CURRENT_DIR_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")
        
#  target_include_directories(${CURRENT_DIR_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
#  target_include_directories(${CURRENT_DIR_NAME} PRIVATE "${ROOT}")

# target_precompile_headers(${CURRENT_DIR_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")


# SetModuleOutput()



# target_include_directories(${CURRENT_DIR_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals)

# source_group(TREE "${ROOT}" FILES ${SOURCES})

# set_target_properties(${CURRENT_DIR_NAME} PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)


# set_target_properties(EntityEngine PROPERTIES
#     OUTPUT_NAME "Eclipsed.ECS"
# )

# find_package(OpenGL REQUIRED)

# target_include_directories(EntityEngine PRIVATE ${CoreEngine_Include})
# target_link_libraries(EntityEngine PRIVATE CoreEngine)





cmake_minimum_required(VERSION 3.19.2)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

set(ROOT "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}")
file(GLOB_RECURSE SOURCES
    "${SOURCE_ROOT}/*.cpp"
    "${SOURCE_ROOT}/*.c"
    "${SOURCE_ROOT}/*.h"
    "${SOURCE_ROOT}/*.hpp"
    "${SOURCE_ROOT}/*.inl"
)

source_group(TREE "${SOURCE_ROOT}" FILES ${SOURCES})

source_group("" FILES 
    ${ROOT}/pch.h
    ${ROOT}/common.hpp
)

if(ECLIPSED_EDITOR)
    add_library(${TARGET_NAME} SHARED)
else()
    add_library(${TARGET_NAME} STATIC)
endif()

set(HEADER_FILES ${SOURCES})
list(FILTER HEADER_FILES INCLUDE REGEX "\\.(h|hpp|inl)$")

set(SOURCE_FILES ${SOURCES})
list(FILTER SOURCE_FILES INCLUDE REGEX "\\.(cpp|c)$")

target_sources(${TARGET_NAME}
    PRIVATE
        ${SOURCE_FILES}
        ${ROOT}/pch.h
        ${ROOT}/common.hpp
    PUBLIC
        FILE_SET HEADERS
        FILES ${HEADER_FILES}
        BASE_DIRS ${ROOT}
)

target_include_directories(${TARGET_NAME} 
    PUBLIC ${ROOT}
    PRIVATE ${SOURCE_ROOT}
    PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals
)

if(TARGET CoreEngine)
    target_link_libraries(${TARGET_NAME} PRIVATE CoreEngine)
endif()

get_target_property(TARGET_TYPE ${TARGET_NAME} TYPE)

if(TARGET_TYPE STREQUAL "SHARED_LIBRARY")
    target_compile_definitions(${TARGET_NAME}
        PRIVATE ${TARGET_NAME}_EXPORTS
        INTERFACE ${TARGET_NAME}_IMPORTS
    )
endif()

target_precompile_headers(${TARGET_NAME} PRIVATE ${ROOT}/pch.h)

set_target_properties(${TARGET_NAME} PROPERTIES 
    OUTPUT_NAME "Eclipsed.ECS"
    FOLDER "Engine/EngineModules"

    UNITY_BUILD ON 
    UNITY_BUILD_BATCH_SIZE 50
)


if(ECLIPSED_EDITOR)
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        
        LIBRARY_OUTPUT_DIRECTORY                "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL     "${EXE_OUTPUT_DIR}/Libs/$<CONFIG>"
        
        RUNTIME_OUTPUT_DIRECTORY                "${EXE_OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${EXE_OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${EXE_OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXE_OUTPUT_DIR}"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${EXE_OUTPUT_DIR}"
    )
else()
    set_target_properties(${TARGET_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        
        LIBRARY_OUTPUT_DIRECTORY                "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL     "${EXE_OUTPUT_DIR}/GameBuildBinary/$<CONFIG>"
        
        RUNTIME_OUTPUT_DIRECTORY                "${EXE_OUTPUT_DIR}/GameBuildBinary/Bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${EXE_OUTPUT_DIR}/GameBuildBinary/Bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${EXE_OUTPUT_DIR}/GameBuildBinary/Bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${EXE_OUTPUT_DIR}/GameBuildBinary/Bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${EXE_OUTPUT_DIR}/GameBuildBinary/Bin"
    )
endif()