function(SetConfigPath CONF_PATH)
    set(CONFIG_PATH "${CONF_PATH}" PARENT_SCOPE)
endfunction()


function(InstallCMakePackage)
    # include(GNUInstallDirs)
    # include(CMakePackageConfigHelpers)

    # set(PROJECT_TARGETS "${PROJECT_KEY}_Targets")

    # install(TARGETS ${TARGET_NAME}
    #     EXPORT "${PROJECT_TARGETS}"
    #     FILE_SET HEADERS

    #     ARCHIVE
    #         DESTINATION ${CMAKE_INSTALL_LIBDIR}

    #     LIBRARY
    #         DESTINATION ${CMAKE_INSTALL_LIBDIR}

    #     RUNTIME
    #         DESTINATION ${CMAKE_INSTALL_BINDIR}
    # )

    # install(EXPORT "${PROJECT_TARGETS}"
    #     FILE "${PROJECT_TARGETS}.cmake"
    #     NAMESPACE Eclipsed::
    #     DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_KEY}"
    # )

    # if(NOT DEFINED CONFIG_PATH) # If config path is not set then fallback to default conf file.
    #     set(CONFIG_PATH "${CMAKE_SOURCE_DIR}/CMake/Config.cmake.in")
    # endif()

    # configure_package_config_file(
    #     ${CONFIG_PATH}
    #     "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_KEY}Config.cmake"
    #     INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_KEY}"
    # )

    # write_basic_package_version_file(
    #     "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_KEY}ConfigVersion.cmake"
    #     VERSION 0.0.0
    #     COMPATIBILITY SameMajorVersion
    # )

    # install(FILES
    #     "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_KEY}Config.cmake"
    #     "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_KEY}ConfigVersion.cmake"
    #     DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_KEY}"
    # )
endfunction()