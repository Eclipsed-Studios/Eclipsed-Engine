cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
set(CMAKE_UNITY_BUILD ON)

project(Eclipsed-Engine LANGUAGES CXX)


# ---- Externals
add_subdirectory(Source/Externals/DiscordSDK)
add_subdirectory(Source/Externals/fmod)
add_subdirectory(Source/Externals/rapidjson)
add_subdirectory(Source/Externals/ImGui)
add_subdirectory(Source/Externals/OpenGL)
add_subdirectory(Source/Externals/SDL3)
add_subdirectory(Source/Externals/stb_image)
add_subdirectory(Source/Externals/Font-Awesome)

# ---- Utilities
add_subdirectory(Source/Utilities)

# ---- Engines
add_subdirectory(Source/Engines/GraphicsEngine)
add_subdirectory(Source/Engines/CoreEngine)
add_subdirectory(Source/Engines/PhysicsEngine)

# ---- Editor
add_subdirectory(Source/Editor)

# ---- Launcher
add_subdirectory(Source/Launcher)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Launcher) 


make_directory("${CMAKE_SOURCE_DIR}/Bin")
file(GLOB DLLs "${CMAKE_SOURCE_DIR}/Tools/DLLs/*")
file(COPY ${DLLs} DESTINATION "${CMAKE_SOURCE_DIR}/Bin")

add_compile_definitions(LEAN_AND_MEAN)


option(EDITOR "Enable the editor" ON)

if(EDITOR)
    add_compile_definitions(ECLIPSED_EDITOR)
endif()



































#keep?
# Move includes to their cmakes?
foreach(target Editor Launcher CoreEngine GraphicsEngine PhysicsEngine Game Utilities)
    if (MSVC)
        target_compile_options(${target} PRIVATE /FI ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
    else()
        target_compile_options(${target} PRIVATE -include ${CMAKE_SOURCE_DIR}/Source/Utilities/pch.h)
    endif()
endforeach()

if (MSVC)
    target_compile_options(CoreEngine PRIVATE /FI ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
    target_compile_options(Game PRIVATE /FI ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
else()
    target_compile_options(CoreEngine PRIVATE -include ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
    target_compile_options(Game PRIVATE -include ${CMAKE_SOURCE_DIR}/Source/Engines/CoreEngine/CoreEngine/ECS/ECS.hpp)
endif()







# Move to editor
set_target_properties(Editor PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)

# Move to launcher
set_target_properties(Launcher PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Bin"
)




# include_directories("${CMAKE_SOURCE_DIR}/Source/Utilities")


# Move to cmakes
target_link_libraries(CoreEngine PRIVATE Utilities)
target_link_libraries(GraphicsEngine PRIVATE Utilities)
target_link_libraries(Editor PRIVATE Utilities)
target_link_libraries(Launcher PRIVATE Utilities)
target_link_libraries(PhysicsEngine PRIVATE Utilities)
target_link_libraries(Game PRIVATE Utilities)

set_target_properties(CoreEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(GraphicsEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Editor PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Launcher PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(PhysicsEngine PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Game PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)
set_target_properties(Utilities PROPERTIES UNITY_BUILD ON UNITY_BUILD_BATCH_SIZE 50)