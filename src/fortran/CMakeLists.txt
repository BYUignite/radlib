if (CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    add_library(radlib_fortran)

    target_sources(radlib_fortran PRIVATE
            rad_module.f90
            c_interface.cc
    )

    target_link_libraries(radlib_fortran radlib)
    target_include_directories(radlib_fortran PRIVATE "${CMAKE_SOURCE_DIR}/c++")

    install(FILES "${CMAKE_BINARY_DIR}/src/fortran/rad_module.mod"
            DESTINATION "${CMAKE_INSTALL_PREFIX}/include")

    install(TARGETS radlib_fortran
            EXPORT radlib_fortranTargets
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            )

    install(EXPORT radlib_fortranTargets
            FILE radlib_fortran.cmake
            NAMESPACE radlib_fortran::
            DESTINATION cmake/radlib_fortran
            )

elseif(!CMAKE_Fortran_COMPILER AND BUILD_FORTRAN_INTERFACE)

    message([FATAL_ERROR] "No Fortran compiler found")

endif()
