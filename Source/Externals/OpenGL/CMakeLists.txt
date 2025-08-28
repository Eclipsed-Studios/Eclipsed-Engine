find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

file(GLOB_RECURSE OPENGL_SOURCES 
"${CMAKE_CURRENT_SOURCE_DIR}/glad/glad.c"
)

add_library(Opengl STATIC ${OPENGL_SOURCES})
target_include_directories(Opengl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(FMOD INTERFACE
    "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/glfw3.lib"
    "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/glfw3_mt.lib"
)

set_target_properties(Opengl PROPERTIES FOLDER "Externals")



set_source_files_properties("${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL/glad/glad.c" PROPERTIES LANGUAGE C)
set_target_properties(Opengl PROPERTIES LINKER_LANGUAGE C)
set_target_properties(Opengl PROPERTIES C_STANDARD 11)
set_target_properties(Opengl PROPERTIES FOLDER "Externals")