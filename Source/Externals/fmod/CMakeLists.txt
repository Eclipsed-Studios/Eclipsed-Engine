cmake_minimum_required(VERSION 3.19.2)

add_library(FMOD INTERFACE)

target_include_directories(FMOD INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(FMOD INTERFACE
    "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fsbank_vc.lib"

    optimized "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmod_vc.lib"
    optimized "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmodstudio_vc.lib"

    debug "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmodL_vc.lib"
    debug "${CMAKE_SOURCE_DIR}/Tools/Libs/fmod/fmodstudioL_vc.lib"
)

set_target_properties(FMOD PROPERTIES FOLDER "Externals")
