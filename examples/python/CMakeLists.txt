
if (PYTHON_EXECUTABLE AND BUILD_CYTHON_INTERFACE)

    set(SETUP_PY_EX    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY_EX} build_ext --inplace -b ../examples/python)")

endif()

