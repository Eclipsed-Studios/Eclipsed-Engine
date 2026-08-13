add_library(stb_image INTERFACE)

target_include_directories(stb_image INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(stb_image PROPERTIES FOLDER "Externals")

    set_target_properties(stb_image PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
    )