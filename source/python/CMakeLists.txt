
find_program(PYTHON_EXECUTABLE NAMES python3 python)

if (PYTHON_EXECUTABLE AND BUILD_CYTHON_INTERFACE)

    set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
    set(SETUP_PY    "${CMAKE_CURRENT_SOURCE_DIR}/setup.py")
    configure_file(${SETUP_PY_IN} ${SETUP_PY})

    set(OUTPUT      "${CMAKE_BINARY_DIR}/python")

    add_custom_command(OUTPUT ${OUTPUT}
                       COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} build_ext --inplace
                       COMMAND cmake -E touch ${OUTPUT})

    add_custom_target(python ALL DEPENDS ${OUTPUT})

    install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} ${SETUP_PY} install --prefix=${CMAKE_INSTALL_PREFIX})")

    FILE(GLOB_RECURSE rcslw_data_files "${RCSLW_DATA_DIR}/*.txt" "${RCSLW_DATA_DIR}/README.md")
    install(FILES ${rcslw_data_files} DESTINATION ${INSTALLED_RCSLW_DATA_DIR})


endif()

