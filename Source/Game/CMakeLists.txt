include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Game)
GenerateCoreApiFile(GAME_API)

CreateStaticProject()

target_link_libraries(Game
    PUBLIC
        EclipsedEngine
)
# SetFolder("Modules")
