cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)


project(Template LANGUAGES CXX)

add_compile_definitions(ENGINE_SETTINGS_PATH=\"${CMAKE_SOURCE_DIR}/Settings/GameSettings.json\")

add_compile_definitions(ENGINE_NAMESPACE=TEMPLATE)

add_subdirectory(Source/Externals/DiscordSDK)
add_subdirectory(Source/Externals/fmod)
add_subdirectory(Source/Externals/rapidjson)
add_subdirectory(Source/Externals/ImGui)
add_subdirectory(Source/Externals/OpenGL)
add_subdirectory(Source/Externals/SDL3)
add_subdirectory(Source/Externals/stb_image)

add_subdirectory(Source/Utilities)

add_subdirectory(Source/PlatformIntegration)

add_subdirectory(Source/Engines/GraphicsEngine)
add_subdirectory(Source/Engines/CoreEngine)
add_subdirectory(Source/Engines/PhysicsEngine)

add_subdirectory(Source/Editor)
add_subdirectory(Source/Game)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Editor) 

set_target_properties(Editor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)

set_target_properties(Game PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)

make_directory("${CMAKE_SOURCE_DIR}/Bin")
file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Tools/DLLs/*")
file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")



include_directories("${CMAKE_SOURCE_DIR}/Source/Utilities")

target_link_libraries(CoreEngine PRIVATE Utilities)
target_link_libraries(GraphicsEngine PRIVATE Utilities)
target_link_libraries(Editor PRIVATE Utilities)
target_link_libraries(Game PRIVATE Utilities)
target_link_libraries(PhysicsEngine PRIVATE Utilities)