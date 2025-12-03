include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

CreateProject(SHARED)

set_target_properties(EclipsedEngine PROPERTIES
    FOLDER "Engine"
)

target_link_libraries(EclipsedEngine PRIVATE 
    AssetEngine
    AudioEngine
    CoreEngine
    EntityEngine
    GraphicsEngine
    InputEngine
    NetworkEngine
    PhysicsEngine
)