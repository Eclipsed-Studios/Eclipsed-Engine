include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Launcher)

message("${OutputName}")
GenerateExecutable("${OutputName}")

target_link_libraries(Launcher PRIVATE 
    Game
)