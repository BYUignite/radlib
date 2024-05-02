if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    add_library(radlib_fortran)
    add_library(radlib_fortran::radlib_fortran ALIAS radlib_fortran)

    target_sources(radlib_fortran PRIVATE rad_module.f90 c_interface.cc)

    target_link_libraries(radlib_fortran radlib)
    target_include_directories(radlib_fortran PRIVATE "${CMAKE_SOURCE_DIR}/c++")

    ############################ Install library

    include(GNUInstallDirs)

    install(FILES "${CMAKE_BINARY_DIR}/src/fortran/rad_module.mod"
            DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

    install(TARGETS radlib_fortran
            EXPORT  radlib_fortran_exp)

    install(EXPORT      radlib_fortran_exp
            FILE        radlib_fortran_exp.cmake
            NAMESPACE   radlib_fortran::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/radlib_fortran")

    install(FILES       "radlib_fortranConfig.cmake"                    # install config files
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/radlib_fortran") # edit file radlibConfig.cmake

elseif(!CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)
    message([FATAL_ERROR] "No Fortran compiler found")
endif()
