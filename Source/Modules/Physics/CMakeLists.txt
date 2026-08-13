include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Physics)
GenerateCoreApiFile(PHYSICS_API)

CreateStaticProject()

target_link_libraries(Physics PUBLIC 
    Core
    box2d
)

SetFolder("Modules")