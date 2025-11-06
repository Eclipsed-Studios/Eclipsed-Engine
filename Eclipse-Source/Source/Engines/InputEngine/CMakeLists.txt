find_package(OpenGL REQUIRED)
cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/InputEngine-Sources.cmake")


add_library(InputEngine STATIC ${INPUT_ENGINE_SOURCES})
AddFilesToFolders("${INPUT_ENGINE_SOURCES}" "${INPUT_ENGINE_ROOT}")

target_precompile_headers(InputEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(InputEngine PROPERTIES FOLDER "Engines")


target_include_directories(InputEngine PRIVATE ${INPUT_ENGINE_ROOT})
target_include_directories(InputEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})




# ---- AssetEngine
include("${CMAKE_SOURCE_DIR}/Source/CMakeSources/AssetEngine-Sources.cmake")
target_include_directories(InputEngine PUBLIC ${ASSET_ENGINE_ROOT})
target_link_libraries(InputEngine PUBLIC AssetEngine)



target_include_directories(InputEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
target_link_libraries(InputEngine PRIVATE OpenGL::GL)
target_link_libraries(InputEngine PRIVATE Opengl)
target_link_libraries(InputEngine PRIVATE "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/nvml.lib")


set_target_properties(InputEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)