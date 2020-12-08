
if (PYTHON_EXECUTABLE AND BUILD_CYTHON_INTERFACE)

    set(SETUP_PY_EX_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY_EX    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    configure_file(${SETUP_PY_EX_IN} ${SETUP_PY_EX})

    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY_EX} build_ext --inplace -b ../examples/python)")

    #-------------- output message to user to update PYTHONPATH environment variable

    set(GETPPCMD_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/get_pythonpath_command.py.in")
    set(GETPPCMD_PY    "${CMAKE_CURRENT_SOURCE_DIR}/get_pythonpath_command.py")
    get_filename_component(PYTHONPATH_PARTIAL "../${CMAKE_INSTALL_PREFIX}/lib" ABSOLUTE)
    configure_file(${GETPPCMD_PY_IN} ${GETPPCMD_PY})
    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${GETPPCMD_PY})")


endif()

