
#################### Doxygen documentation

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doxygen 
        COMMENT "Building doxygen documentation"
        COMMAND rm -rf ../../docs/doxygen/html
        COMMAND mkdir  ../../docs/doxygen/html
        COMMAND doxygen -s ../../docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
    )
else()
    message("Cannot build documentation because doxygen was not found")
endif()
