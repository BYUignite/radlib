find_program(Python3_EXECUTABLE NAMES python python3)
#find_package(Python3 COMPONENTS Interpreter)

if (Python3_EXECUTABLE AND BUILD_PYTHON_INTERFACE)

    set(SETUP_PY_IN "${CMAKE_CURRENT_LIST_DIR}/setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_LIST_DIR}/setup.py")
    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    set(OUTPUT      "${CMAKE_BINARY_DIR}/python")

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${Python3_EXECUTABLE} ${SETUP_PY} build_ext --inplace
                       COMMAND cmake -E touch ${OUTPUT})

    add_custom_target(python ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${Python3_EXECUTABLE} ${SETUP_PY} install --prefix=${CMAKE_INSTALL_PREFIX})")

elseif(!Python3_EXECUTABLE AND BUILD_PYTHON_INTERFACE)

    message([FATAL_ERROR] "Python not found")

endif()