if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE AND BUILD_FORTRAN_EXAMPLES)

    set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib") # to include sootlib (built in this project)
    #set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)           # only needed if examples dep on an external lib

    add_executable(            simple_interface_fort.x simple_interface_fort.f90)
    target_include_directories(simple_interface_fort.x PRIVATE "${CMAKE_BINARY_DIR}/src/fortran")
    target_link_libraries(     simple_interface_fort.x radlib radlib_fortran -fPIC)
    install(TARGETS            simple_interface_fort.x DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

elseif(!CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_EXAMPLES)

    message([FATAL_ERROR] "No Fortran compiler found")

endif()
