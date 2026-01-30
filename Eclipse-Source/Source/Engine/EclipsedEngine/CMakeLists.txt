include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

option(BUILD_GAME "Build game as static library." FALSE)
message(TESTING -  ${BUILD_GAME})

if(BUILD_GAME)
    CreateProject(STATIC)
else()
    CreateProject(SHARED)
endif()

set_target_properties(EclipsedEngine PROPERTIES
    FOLDER "Engine"
)

target_include_directories(EclipsedEngine PRIVATE "${CMAKE_SOURCE_DIR}/Source/Externals/asio")

target_link_libraries(EclipsedEngine PUBLIC 
    AssetEngine
    AudioEngine
    CoreEngine
    EntityEngine
    GraphicsEngine
    NetworkEngine
    PhysicsEngine

    ImGui
)


if(BUILD_GAME)
    target_link_libraries(EclipsedEngine PUBLIC Game)
endif()