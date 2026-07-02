include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")


if(INCLUDE_GAME)
    CreateProject(STATIC)
else()
    CreateProject(SHARED)
endif()

set_target_properties(EclipsedRuntime PROPERTIES
    FOLDER "Engine"
    OUTPUT_NAME "Eclipsed.Runtime"
)

target_include_directories(EclipsedRuntime PRIVATE "${CMAKE_SOURCE_DIR}/Source/Externals/asio")

target_link_libraries(EclipsedRuntime PRIVATE 
    AssetEngine
    AudioEngine
    CoreEngine
    EntityEngine
    GraphicsEngine
    PhysicsEngine
    EclipsedEngine

    ImGui
)

add_compile_definitions(
    ECLIPSED_RUNTIME
)

if(${ENABLE_NETWORKING})
    target_link_libraries(EclipsedRuntime PRIVATE NetworkEngine)
endif()

if(${ENABLE_STEAM_SDK})
    target_link_libraries(EclipsedRuntime PRIVATE "${CMAKE_SOURCE_DIR}/Source/Externals/steamsdk/lib/win64/steam_api64.lib")
endif()


if(INCLUDE_GAME)
    target_link_libraries(EclipsedRuntime PRIVATE Game)
endif()