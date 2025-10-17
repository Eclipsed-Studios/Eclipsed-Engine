find_package(OpenGL REQUIRED)

cmake_minimum_required(VERSION 3.19.2)

include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")
include("${CMAKE_SOURCE_DIR}/Source/CMakeSOurces/GraphicsEngine-Sources.cmake")

add_library(GraphicsEngine STATIC ${GRAPHICS_ENGINE_SOURCES})
AddFilesToFolders("${GRAPHICSENGINE_SOURCES}" "${GRAPHICS_ENGINE_ROOT}")

target_precompile_headers(GraphicsEngine PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/pch.h")

set_target_properties(GraphicsEngine PROPERTIES FOLDER "Engines")


# ---- Graphics Engine
target_include_directories(GraphicsEngine PRIVATE ${GRAPHICS_ENGINE_ROOT}/GraphicsEngine)


# ---- Freetype
target_include_directories(GraphicsEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/FreeType)
target_link_libraries(GraphicsEngine PRIVATE "${CMAKE_SOURCE_DIR}/Tools/Libs/FreeType/freetyped.lib")


# ---- OpenGL and GLFW
target_include_directories(GraphicsEngine PRIVATE ${CMAKE_SOURCE_DIR}/Source/Externals/OpenGL)
target_link_libraries(GraphicsEngine PRIVATE OpenGL::GL)
target_link_libraries(GraphicsEngine PRIVATE Opengl)
target_link_libraries(GraphicsEngine PRIVATE "${CMAKE_SOURCE_DIR}/Tools/Libs/GLFW/nvml.lib")