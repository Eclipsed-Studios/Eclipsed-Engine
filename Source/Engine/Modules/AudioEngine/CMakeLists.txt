include("${CMAKE_SOURCE_DIR}/Tools/CMake/common.cmake")

CreateProject(STATIC)

set_target_properties(AudioEngine PROPERTIES
    OUTPUT_NAME "Eclipsed.Audio"
)

target_link_libraries(AudioEngine PRIVATE 
    CoreEngine 
)

target_link_libraries(AudioEngine PRIVATE FMOD)