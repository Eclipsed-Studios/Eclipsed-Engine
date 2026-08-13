add_library(rapidjson INTERFACE)

target_include_directories(rapidjson INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set_target_properties(rapidjson PROPERTIES
    FOLDER "Externals"
    EXCLUDE_FROM_ALL TRUE
)

    set_target_properties(rapidjson PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
    )