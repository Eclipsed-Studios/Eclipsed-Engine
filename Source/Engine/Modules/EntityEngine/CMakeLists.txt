cmake_minimum_required(VERSION 3.23)

# ============================================================
# Module name
# ============================================================

# Get the folder name as the target name
get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

# Current module root
set(ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

# Source folder containing actual code
set(SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}")


# ============================================================
# Collect source files
# ============================================================

file(GLOB_RECURSE SOURCES
    "${SOURCE_ROOT}/*.cpp"
    "${SOURCE_ROOT}/*.c"
    "${SOURCE_ROOT}/*.h"
    "${SOURCE_ROOT}/*.hpp"
    "${SOURCE_ROOT}/*.inl"
)


# Add files to Visual Studio filters
source_group(TREE "${SOURCE_ROOT}" FILES ${SOURCES})

source_group("" FILES
    ${ROOT}/pch.h
)


# ============================================================
# Create library
# ============================================================

if(ECLIPSED_EDITOR)
    add_library(${TARGET_NAME} SHARED)
else()
    add_library(${TARGET_NAME} STATIC)
endif()


# Separate headers and source files
set(HEADER_FILES ${SOURCES})
list(FILTER HEADER_FILES INCLUDE REGEX "\\.(h|hpp|inl)$")

set(SOURCE_FILES ${SOURCES})
list(FILTER SOURCE_FILES INCLUDE REGEX "\\.(cpp|c)$")


# ============================================================
# Add files to target
# ============================================================

target_sources(${TARGET_NAME}
    PRIVATE
        ${SOURCE_FILES}
        ${ROOT}/pch.h

    PUBLIC
        FILE_SET HEADERS
        TYPE HEADERS
        BASE_DIRS
            ${ROOT}
        FILES
            ${HEADER_FILES}
)


# ============================================================
# Include directories
# ============================================================

#
# IMPORTANT:
#
# PUBLIC include directories are exported when using:
#
#     install(EXPORT ...)
#
# Therefore absolute source paths cannot be used directly.
#
# BUILD_INTERFACE:
#   Used when building the engine itself.
#
# INSTALL_INTERFACE:
#   Used by external projects after installation.
#

target_include_directories(${TARGET_NAME}

    PUBLIC

        # During development:
        # Allows:
        # #include <EntityEngine/...>
        #
        $<BUILD_INTERFACE:${ROOT}>

        # After installation:
        # Headers are installed into include/
        #
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>


    PRIVATE

        # Internal source directory
        ${SOURCE_ROOT}

        # Third party dependencies
        ${CMAKE_SOURCE_DIR}/Source/Externals
)


# ============================================================
# Link dependencies
# ============================================================

if(TARGET CoreEngine)
    target_link_libraries(${TARGET_NAME}
        PRIVATE
            CoreEngine
    )
endif()


# ============================================================
# DLL export definitions
# ============================================================

get_target_property(TARGET_TYPE ${TARGET_NAME} TYPE)

if(TARGET_TYPE STREQUAL "SHARED_LIBRARY")

    target_compile_definitions(${TARGET_NAME}
        PRIVATE
            ${TARGET_NAME}_EXPORTS

        INTERFACE
            ${TARGET_NAME}_IMPORTS
    )

endif()


# ============================================================
# Precompiled headers
# ============================================================

target_precompile_headers(${TARGET_NAME}
    PRIVATE
        ${ROOT}/pch.h
)


# ============================================================
# General target properties
# ============================================================

set_target_properties(${TARGET_NAME}
    PROPERTIES

        OUTPUT_NAME
            "Eclipsed.ECS"

        FOLDER
            "Engine/EngineModules"

        UNITY_BUILD
            ON

        UNITY_BUILD_BATCH_SIZE
            50
)


# ============================================================
# Output directories
# ============================================================

if(ECLIPSED_EDITOR)

    set(LIB_OUTPUT
        "${EXE_OUTPUT_DIR}/Libs/"
    )

    set(BIN_OUTPUT
        "${EXE_OUTPUT_DIR}"
    )

else()

    set(LIB_OUTPUT
        "${EXE_OUTPUT_DIR}/GameBuildBinary"
    )

    set(BIN_OUTPUT
        "${EXE_OUTPUT_DIR}/GameBuildBinary/Bin"
    )

endif()


set_target_properties(${TARGET_NAME}
    PROPERTIES

        ARCHIVE_OUTPUT_DIRECTORY
            ${LIB_OUTPUT}

        LIBRARY_OUTPUT_DIRECTORY
            ${LIB_OUTPUT}

        RUNTIME_OUTPUT_DIRECTORY
            ${BIN_OUTPUT}
)


set_target_properties(${TARGET_NAME}
    PROPERTIES

        # Non-configuration specific (these get overridden by config-specific ones)
        ARCHIVE_OUTPUT_DIRECTORY
            ${LIB_OUTPUT}

        LIBRARY_OUTPUT_DIRECTORY
            ${LIB_OUTPUT}

        RUNTIME_OUTPUT_DIRECTORY
            ${BIN_OUTPUT}

        # Configuration-specific - set these to the SAME values to prevent Debug/Release subfolders
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG
            ${LIB_OUTPUT}

        LIBRARY_OUTPUT_DIRECTORY_DEBUG
            ${LIB_OUTPUT}

        RUNTIME_OUTPUT_DIRECTORY_DEBUG
            ${BIN_OUTPUT}

        ARCHIVE_OUTPUT_DIRECTORY_RELEASE
            ${LIB_OUTPUT}

        LIBRARY_OUTPUT_DIRECTORY_RELEASE
            ${LIB_OUTPUT}

        RUNTIME_OUTPUT_DIRECTORY_RELEASE
            ${BIN_OUTPUT}

        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO
            ${LIB_OUTPUT}

        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO
            ${LIB_OUTPUT}

        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO
            ${BIN_OUTPUT}

        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL
            ${LIB_OUTPUT}

        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL
            ${LIB_OUTPUT}

        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL
            ${BIN_OUTPUT}
)


# ============================================================
# Installation
# ============================================================

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)


#
# Install:
#
#   lib/
#   bin/
#   include/
#
# FILE_SET automatically installs headers.
#

install(TARGETS ${TARGET_NAME}

    EXPORT ${TARGET_NAME}Targets

    FILE_SET HEADERS

    ARCHIVE
        DESTINATION ${CMAKE_INSTALL_LIBDIR}

    LIBRARY
        DESTINATION ${CMAKE_INSTALL_LIBDIR}

    RUNTIME
        DESTINATION ${CMAKE_INSTALL_BINDIR}

)


# ============================================================
# Export CMake package
# ============================================================

install(EXPORT ${TARGET_NAME}Targets
    FILE
        Eclipsed-EngineTargets.cmake  # Change this to match
    NAMESPACE
        Eclipsed::
    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}
)


# ============================================================
# Generate Config files
# ============================================================

configure_package_config_file(

    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in

    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Config.cmake

    INSTALL_DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}

)


write_basic_package_version_file(

    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake

    VERSION
        0.0.0

    COMPATIBILITY
        SameMajorVersion

)


install(FILES

    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}Config.cmake

    ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}ConfigVersion.cmake

    DESTINATION
        ${CMAKE_INSTALL_LIBDIR}/cmake/${TARGET_NAME}

)