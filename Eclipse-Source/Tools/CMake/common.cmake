function(AddUnityTargetEXE TARGET_NAME)
    set(UNITY_BUILD_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_unity.cpp)
    
    file(WRITE ${UNITY_BUILD_FILE} "// Unity build file generated through cmake for ${TARGET_NAME}\n\n")
    foreach(SRC_FILE ${ARGN})
        file(APPEND ${UNITY_BUILD_FILE} "#include \"${SRC_FILE}\"\n")
    endforeach()
    
    if(WIN32)
        add_executable(${TARGET_NAME} WIN32 ${UNITY_BUILD_FILE})
    endif(WIN32)
    if(UNIX)
        add_executable(${TARGET_NAME} ${UNITY_BUILD_FILE})
    endif(UNIX)

    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()

function(AddUnityTargetLIB TARGET_NAME)
    set(UNITY_BUILD_FILE ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}_unity.cpp)
    
    file(WRITE ${UNITY_BUILD_FILE} "// Unity build file generated through cmake for ${TARGET_NAME}\n\n")
    foreach(SRC_FILE ${ARGN})
        file(APPEND ${UNITY_BUILD_FILE} "#include \"${SRC_FILE}\"\n")
    endforeach()
    
    add_library(${TARGET_NAME} STATIC ${UNITY_BUILD_FILE})

    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
endfunction()