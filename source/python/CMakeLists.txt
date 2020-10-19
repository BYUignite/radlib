add_custom_target(python 
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND python3 setup.py build_ext --inplace
    COMMENT "BUILDING PYTHON (CYTHON)"
    VERBATIM
)
