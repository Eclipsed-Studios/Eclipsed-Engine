include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

CreateProject(STATIC)

find_package(OpenGL REQUIRED)

target_include_directories(InputEngine PRIVATE ${CoreEngine_Include})
target_link_libraries(InputEngine PRIVATE CoreEngine)

target_include_directories(InputEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
target_link_libraries(InputEngine PRIVATE OpenGL::GL)
target_link_libraries(InputEngine PRIVATE Opengl)
target_link_libraries(InputEngine PRIVATE "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/nvml.lib")