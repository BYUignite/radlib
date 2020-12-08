
if (PYTHON_EXECUTABLE AND BUILD_CYTHON_INTERFACE)

    set(SETUP_PY_EX_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY_EX    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    configure_file(${SETUP_PY_EX_IN} ${SETUP_PY_EX})

    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY_EX} build_ext --inplace -b ../examples/python)")

endif()

