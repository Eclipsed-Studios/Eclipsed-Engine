include("${CMAKE_SOURCE_DIR}/CMake/common.cmake")

SetProjectKey(Networking)
GenerateCoreApiFile(NETWORKING_API)

CreateStaticProject()

target_link_libraries(Networking PUBLIC 
    Core
    steamsdk
    asio

    PRIVATE
        "wininet.lib"
)

SetFolder("Modules")