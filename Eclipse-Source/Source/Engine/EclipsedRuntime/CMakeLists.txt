cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/EclipsedRuntime-Sources.cmake")


add_library(EclipsedRuntime SHARED ${ECLIPSED_RUNTIME_SOURCES})
AddFilesToFolders("${ECLIPSED_RUNTIME_SOURCES}" "${ECLIPSED_RUNTIME_ROOT}")

target_compile_definitions(EclipsedRuntime PRIVATE ECLIPSED_EXPORT_RUNTIME)
target_include_directories(EclipsedRuntime PUBLIC ${ECLIPSED_RUNTIME_ROOT} ${IMGUI_ROOT})


set_target_properties(EclipsedRuntime PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Libs"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/Bin"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/Bin"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_SOURCE_DIR}/Bin"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_SOURCE_DIR}/Bin"
)


target_precompile_headers(EclipsedRuntime PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(EclipsedRuntime PROPERTIES FOLDER "Engine")

# target_include_directories(EclipsedRuntime PRIVATE ${ECLIPSED_RUNTIME_ROOT})
target_include_directories(EclipsedRuntime PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ---- CoreEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/CoreEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${CORE_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC CoreEngine)


# ---- InputEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/InputEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${INPUT_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC InputEngine)


# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC AssetEngine)


# ---- GraphicsEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/GraphicsEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${GRAPHICS_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC GraphicsEngine)


# ---- Physics Engine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/PhysicsEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${PHYSICS_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC PhysicsEngine)


# ---- EntityEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/EntityEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${ENTITY_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC EntityEngine)


# ---- AudioEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AudioEngine-Sources.cmake")
target_include_directories(EclipsedRuntime PUBLIC ${AUDIO_ENGINE_ROOT})
target_link_libraries(EclipsedRuntime PUBLIC AudioEngine)


target_include_directories(EclipsedRuntime PUBLIC ${IMGUI_ROOT})
target_link_libraries(EclipsedRuntime PRIVATE ImGui)




set_target_properties(EclipsedRuntime PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)