add_library(box2d INTERFACE)

target_include_directories(box2d INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(box2d INTERFACE
    optimized "${CMAKE_CURRENT_SOURCE_DIR}/Libs/box2d.lib"

    debug "${CMAKE_CURRENT_SOURCE_DIR}/Libs/box2d-d.lib"
)

set_target_properties(box2d PROPERTIES FOLDER "Externals")

    set_target_properties(box2d PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin/Externals/Libs/$<CONFIG>"
    )