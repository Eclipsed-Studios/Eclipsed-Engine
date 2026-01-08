include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

CreateProject(STATIC)

find_package(OpenGL REQUIRED)

target_include_directories(NetworkEngine PRIVATE ${CoreEngine_Include})

target_link_libraries(NetworkEngine PRIVATE CoreEngine)
target_link_libraries(NetworkEngine PRIVATE EntityEngine)
target_link_libraries(NetworkEngine PRIVATE AssetEngine)

target_include_directories(NetworkEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source/Externals/asio")

target_include_directories(NetworkEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source/Engine/EclipsedEngine")
target_include_directories(NetworkEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source/Engine/Modules/EntityEngine")
target_include_directories(NetworkEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source/Engine/Modules/AssetEngine")
