include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Editor)
GeneratePCHFile()

GenerateExecutable()

target_link_libraries(Editor
    PUBLIC
        EclipsedEngine
)