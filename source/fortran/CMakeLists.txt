
find_program(FORTRAN_COMPILER NAMES python python3)

if (FORTRAN_COMPILER AND BUILD_FORTRAN_INTERFACE)

    add_library(radlib_fortran "")

    target_sources(radlib_fortran
        PRIVATE
            rad_module.f90
            c_interface.cc
    )

    target_link_libraries(radlib_fortran radlib)
    target_include_directories(radlib_fortran PRIVATE "${CMAKE_SOURCE_DIR}/c++")

    install(TARGETS radlib_fortran
            LIBRARY DESTINATION lib)

endif()
