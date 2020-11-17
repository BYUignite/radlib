
find_program(PYTHON_EXECUTABLE NAMES python python3)

if (PYTHON_EXECUTABLE AND BUILD_CYTHON_INTERFACE)

    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    set(OUTPUT      "${CMAKE_BINARY_DIR}/python")

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} build_ext --inplace
                       COMMAND cmake -E touch ${OUTPUT})

    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    add_custom_target(python ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} install --prefix=${CMAKE_INSTALL_PREFIX})")

    FILE(GLOB_RECURSE rcslw_data_files "${RCSLW_DATA_DIR}/*.txt" "${RCSLW_DATA_DIR}/README.md")
    install(FILES ${rcslw_data_files} DESTINATION ${INSTALLED_RCSLW_DATA_DIR})


    #-------------- output message to user to update PYTHONPATH environment variable

    set(GETPPCMD_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/get_pythonpath_command.py.in")
    set(GETPPCMD_PY    "${CMAKE_CURRENT_SOURCE_DIR}/get_pythonpath_command.py")
    get_filename_component(PYTHONPATH_PARTIAL "../${CMAKE_INSTALL_PREFIX}/lib" ABSOLUTE)
    configure_file(${GETPPCMD_PY_IN} ${GETPPCMD_PY})
    install(CODE "MESSAGE(\"\n\n*************** Installation complete *****************.\")")
    install(CODE "MESSAGE(\"\n  To use the Python interface, update your PYTHONPATH environment variable:\")")
    install(CODE "MESSAGE(\"\n  For example, on Linux/MAC Put the following in your .bashrc file:\")")
    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${GETPPCMD_PY})")

endif()

