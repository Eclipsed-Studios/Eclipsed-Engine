function(SetProjectKey KEY)
    set(PROJECT_KEY ${KEY} PARENT_SCOPE)
endfunction()

function(CreateProject TYPE KEY)
    get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

    set(TARGET_NAME ${TARGET_NAME} PARENT_SCOPE)

    set(ROOT "${CMAKE_CURRENT_SOURCE_DIR}")

    set(SOURCE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}")
    

    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "${SOURCE_ROOT}/*.cpp"
        "${SOURCE_ROOT}/*.c"
        "${SOURCE_ROOT}/*.h"
        "${SOURCE_ROOT}/*.hpp"
        "${SOURCE_ROOT}/*.inl"
    )

    source_group(TREE "${SOURCE_ROOT}" FILES ${SOURCES})

    source_group("" FILES
        ${ROOT}/pch.h
    )

    add_library(${TARGET_NAME} ${TYPE})

    set(HEADER_FILES ${SOURCES})
    list(FILTER HEADER_FILES INCLUDE REGEX "\\.(h|hpp|inl)$")

    set(SOURCE_FILES ${SOURCES})
    list(FILTER SOURCE_FILES INCLUDE REGEX "\\.(cpp|c)$")

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

    target_include_directories(${TARGET_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${ROOT}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

    PRIVATE
        ${SOURCE_ROOT}
        ${CMAKE_SOURCE_DIR}/Source/Externals
    )

    if(TARGET CoreEngine AND NOT TARGET_NAME STREQUAL "CoreEngine")
        target_link_libraries(${TARGET_NAME}
            PRIVATE
                CoreEngine
        )
    endif()


    get_target_property(TARGET_TYPE ${TARGET_NAME} TYPE)

    if(TYPE STREQUAL "SHARED")
        target_compile_definitions(${TARGET_NAME}
            PRIVATE
                ${TARGET_NAME}_EXPORTS

            INTERFACE
                ${TARGET_NAME}_IMPORTS
        )
    endif()

    target_precompile_headers(${TARGET_NAME}
        PRIVATE
            ${ROOT}/pch.h
    )

    set_target_properties(${TARGET_NAME}
        PROPERTIES
            OUTPUT_NAME "Eclipsed.${PROJECT_KEY}"
            FOLDER "Engine/EngineModules"
            UNITY_BUILD ON
            UNITY_BUILD_BATCH_SIZE 50
    )

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
            ARCHIVE_OUTPUT_DIRECTORY ${LIB_OUTPUT}
            LIBRARY_OUTPUT_DIRECTORY ${LIB_OUTPUT}
            RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT}
    )


    SetModuleOutputPaths()
endfunction()



function(SetModuleOutputPaths)
    if(ECLIPSED_EDITOR)
        set_target_properties(${CURRENT_DIR_NAME} PROPERTIES
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

            FOLDER "Engine/EngineModules"
        )
    else()
        set_target_properties(${CURRENT_DIR_NAME} PROPERTIES
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
endfunction()




function(CreateSharedProject)
    CreateProject(SHARED ${PROJECT_KEY})
    
    set(TARGET_NAME ${TARGET_NAME} PARENT_SCOPE)
    set(ROOT ${ROOT} PARENT_SCOPE)
    set(SOURCE_ROOT ${SOURCE_ROOT} PARENT_SCOPE)
endfunction()

function(CreateStaticProject)
    CreateProject(STATIC ${PROJECT_KEY})

    set(TARGET_NAME ${TARGET_NAME} PARENT_SCOPE)
    set(ROOT ${ROOT} PARENT_SCOPE)
    set(SOURCE_ROOT ${SOURCE_ROOT} PARENT_SCOPE)
endfunction()