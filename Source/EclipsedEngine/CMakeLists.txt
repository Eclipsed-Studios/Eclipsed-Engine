include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(EclipsedEngine)
GenerateCoreApiFile(ECL_API)
GeneratePCHFile()

CreateSharedProject()

target_link_libraries(EclipsedEngine
    PUBLIC
        # Core  
        # Input  
        # Audio  
        # Assets  
        # ECS
        # Renderer
        # Physics
        # Networking

    PRIVATE
        ImGui
)