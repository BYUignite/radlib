if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE AND BUILD_FORTRAN_EXAMPLES)

    add_executable(simple_interface_fort.x)
    target_sources(simple_interface_fort.x PRIVATE simple_interface_fort.f90)
    target_link_libraries(simple_interface_fort.x radlib radlib_fortran -fPIC)
    target_include_directories(simple_interface_fort.x PRIVATE "${CMAKE_BINARY_DIR}/src/fortran")

    set_property(TARGET simple_interface_fort.x PROPERTY LINKER_LANGUAGE Fortran)

    install(TARGETS simple_interface_fort.x DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

elseif(!CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_EXAMPLES)

    message([FATAL_ERROR] "No Fortran compiler found")

endif()
