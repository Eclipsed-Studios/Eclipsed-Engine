find_package(OpenGL REQUIRED)


file(GLOB_RECURSE OPENGL_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}/*.*"
)

get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)


add_library(OpenGL STATIC ${OPENGL_SOURCES})


target_link_libraries(OpenGL INTERFACE
    ${LIB_FILES}
)


target_include_directories(OpenGL
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}

    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}
)

set_target_properties(OpenGL PROPERTIES 
    FOLDER "Externals"
    EXCLUDE_FROM_ALL TRUE
)

set_target_properties(OpenGL PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Libs/Externals/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin/Libs/Externals/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin/Libs/Externals/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin/Libs/Externals/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin/Libs/Externals/$<CONFIG>"
    ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin/Libs/Externals/$<CONFIG>"
)

file(GLOB LIB_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Libs/*.lib"
)

target_link_libraries(OpenGL INTERFACE
    ${LIB_FILES}
)
