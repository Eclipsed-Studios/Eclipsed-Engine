include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(OpenGL_Renderer)

CreateSharedProject()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/OpenGL")

target_link_libraries(OpenGL_Renderer 
    PUBLIC 
        EclipsedEngine

    PRIVATE
        OpenGL
)

SetFolder("Plugins")


get_target_property(TYPE OpenGL_Renderer TYPE)
get_target_property(LINKS OpenGL_Renderer LINK_LIBRARIES)

message(STATUS "OpenGL_Renderer TYPE: ${TYPE}")
message(STATUS "OpenGL_Renderer LINKS: ${LINKS}")