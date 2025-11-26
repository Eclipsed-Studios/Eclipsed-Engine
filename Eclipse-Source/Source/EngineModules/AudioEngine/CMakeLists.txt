include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

CreateProject(STATIC)

target_include_directories(GraphicsEngine PRIVATE ${CoreEngine_Include})
target_link_libraries(GraphicsEngine PRIVATE CoreEngine)