add_library(FreeType INTERFACE)

target_include_directories(FreeType INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FreeType INTERFACE
    optimized "${CMAKE_CURRENT_SOURCE_DIR}/Libs/freetype.lib"
    debug "${CMAKE_CURRENT_SOURCE_DIR}/Libs/freetyped.lib"
)

set_target_properties(FreeType PROPERTIES FOLDER "Externals")

    set_target_properties(FreeType PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
    )