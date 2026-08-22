include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(EclipsedEngine)
GenerateCoreApiFile(ECL_API)

CreateStaticProject()

target_link_libraries(EclipsedEngine
    PUBLIC
        Core  
        Input  
        Audio  
        Assets  
        ECS
        Renderer
        Physics
        Networking
        ImGui
)
