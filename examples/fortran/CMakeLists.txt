find_program(FORTRAN_COMPILER NAMES gfortran)

if (FORTRAN_COMPILER AND BUILD_FORTRAN_INTERFACE)

    add_executable(simple_interface_fort.x "")
    target_sources(simple_interface_fort.x PRIVATE simple_interface_fort.f90)
    target_link_libraries(simple_interface_fort.x radlib radlib_fortran -lgfortran -shared)
    target_include_directories(simple_interface_fort.x PRIVATE "${CMAKE_BINARY_DIR}/fortran")

    install(TARGETS simple_interface_fort.x DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

endif()
