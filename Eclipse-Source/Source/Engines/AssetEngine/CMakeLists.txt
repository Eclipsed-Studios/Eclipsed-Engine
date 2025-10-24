find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")

add_library(AssetEngine STATIC ${ASSET_ENGINE_SOURCES})

set(ASSETS "${ASSET_ENGINE_ROOT}/AssetEngine")
AddFilesToFolders("${ASSET_ENGINE_SOURCES}" "${ASSETS}")

target_precompile_headers(AssetEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(AssetEngine PROPERTIES FOLDER "Engines")


# ---- Graphics Engine
target_include_directories(AssetEngine PRIVATE ${GRAPHICASSET_ENGINE_ROOTS_ENGINE_ROOT})
target_include_directories(AssetEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


target_include_directories(AssetEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/stbi_image/)

# ---- Freetype
target_include_directories(AssetEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/FreeType)
target_link_libraries(AssetEngine PRIVATE "${CMAKE_SOURCE_DIR}/Tools/Libs/FreeType/freetyped.lib")


# ---- OpenGL and GLFW
target_include_directories(AssetEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
target_link_libraries(AssetEngine PRIVATE OpenGL::GL)
target_link_libraries(AssetEngine PRIVATE Opengl)
target_link_libraries(AssetEngine PRIVATE "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/nvml.lib")


set_target_properties(AssetEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)