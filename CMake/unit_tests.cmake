function(GenerateUnitTest)
    file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/UnitTests")
    set(FILE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/UnitTests/main.cpp")

if(NOT EXISTS "${FILE_PATH}")
    file(WRITE "${FILE_PATH}"
        "#pragma once\n\n"
        "#include <iostream>\n\n"
        "void main()\n"
        "{\n"
        "\tstd::cout << \"This is a unit test\" << std::endl;\n"
        "}\n"
    )
endif()

    get_filename_component(TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
    project(${TARGET_NAME}.UnitTests LANGUAGES CXX)

    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/UnitTests/*.*"
    )

    add_executable(${TARGET_NAME}.UnitTests ${TEST_SOURCES})

    target_link_libraries(${TARGET_NAME}.UnitTests
        PRIVATE
            ${TARGET_NAME}
    )

    set_target_properties(${TARGET_NAME}.UnitTests PROPERTIES
        FOLDER "UnitTests"
    )

    source_group(
        TREE "${CMAKE_CURRENT_SOURCE_DIR}/UnitTests"
        FILES ${TEST_SOURCES}
    )

    set_target_properties(${TARGET_NAME}.UnitTests PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin"
        ARCHIVE_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin"
        ARCHIVE_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin"
        ARCHIVE_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin"
        ARCHIVE_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin"
    
        LIBRARY_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin"
        LIBRARY_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin"
        LIBRARY_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin"
        LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin"
        LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin"
    
        RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/Bin"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG          "${CMAKE_SOURCE_DIR}/Bin"
        RUNTIME_OUTPUT_DIRECTORY_RELEASE        "${CMAKE_SOURCE_DIR}/Bin"
        RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin"
        RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL     "${CMAKE_SOURCE_DIR}/Bin"
    )
endfunction()