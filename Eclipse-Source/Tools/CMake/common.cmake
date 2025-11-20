# function(AddUnityTargetEXE TARGET_NAME)
#     set(UNITY_BUILD_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_unity.cpp)
    
#     file(WRITE ${UNITY_BUILD_FILE} "// Unity build file generated through cmake for ${TARGET_NAME}\n\n")
#     foreach(SRC_FILE ${ARGN})
#         file(APPEND ${UNITY_BUILD_FILE} "#include \"${SRC_FILE}\"\n")
#     endforeach()
    
#     if(WIN32)
#         add_executable(${TARGET_NAME} WIN32 ${UNITY_BUILD_FILE})
#     endif(WIN32)
#     if(UNIX)
#         add_executable(${TARGET_NAME} ${UNITY_BUILD_FILE})
#     endif(UNIX)

#     target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# endfunction()

# function(AddUnityTargetLIB TARGET_NAME)
#     set(UNITY_BUILD_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_unity.cpp)
    
#     file(WRITE ${UNITY_BUILD_FILE} "// Unity build file generated through cmake for ${TARGET_NAME}\n\n")
#     foreach(SRC_FILE ${ARGN})
#         file(APPEND ${UNITY_BUILD_FILE} "#include \"${SRC_FILE}\"\n")
#     endforeach()
    
#     add_library(${TARGET_NAME} STATIC ${UNITY_BUILD_FILE})

#     target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
# endfunction()


# function(AddFilesToFolders SOURCES REL_PATH)
#     foreach(source_file IN LISTS SOURCES)
#         file(RELATIVE_PATH source_path "${REL_PATH}" "${source_file}")
#         get_filename_component(source_group "${source_path}" PATH)
#         if(NOT source_group STREQUAL "")
#             source_group("${source_group}" FILES "${source_file}")
#         else()
#             source_group("" FILES "${source_file}")
#         endif()
#     endforeach()
# endfunction()


function(AddFilesToFolders SOURCES REL_PATH)
    get_filename_component(base_name "${REL_PATH}" NAME)
    foreach(source_file IN LISTS SOURCES)
        file(RELATIVE_PATH source_path "${REL_PATH}" "${source_file}")
        get_filename_component(source_group "${source_path}" PATH)
        
        # Remove duplicate top-level folder if it matches base folder
        string(REGEX REPLACE "^${base_name}[\\/]" "" source_group "${source_group}")
        
        if(NOT source_group STREQUAL "")
            source_group("${source_group}" FILES "${source_file}")
        else()
            source_group("" FILES "${source_file}")
        endif()
    endforeach()
endfunction()