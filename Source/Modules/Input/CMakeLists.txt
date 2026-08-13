include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Input)
GenerateCoreApiFile(INPUT_API)

CreateStaticProject()

target_link_libraries(Input PUBLIC 
    Core
    OpenGL
)

SetFolder("Modules")