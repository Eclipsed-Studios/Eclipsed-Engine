include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Launcher)

GenerateExecutable()

target_link_libraries(Launcher PRIVATE 
    EclipsedEngine
)