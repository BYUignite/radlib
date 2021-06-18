add_library(radlib "")

#################### Compile options

target_compile_features(radlib PUBLIC cxx_std_11)

#-------- create macro so that source code can access the rcslw data files
add_definitions(-DRCSLW_DATA_DIR="${INSTALLED_RCSLW_DATA_DIR}")

#################### Local source files

target_sources(radlib PRIVATE
        rad.h
        rad_planck_mean.cc rad_planck_mean.h
        rad_wsgg.cc rad_wsgg.h
        rad_rcslw.cc rad_rcslw.h
        multilinear_interpolation.h
)

set_target_properties(radlib PROPERTIES PUBLIC_HEADER "rad.h;rad_planck_mean.h;rad_rcslw.h;rad_wsgg.h;multilinear_interpolation.h")

#################### installation

install(TARGETS radlib
        EXPORT radlibTargets
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        )

install(EXPORT radlibTargets
        FILE radlib.cmake
        NAMESPACE radlib::
        DESTINATION cmake/radlib
        )
