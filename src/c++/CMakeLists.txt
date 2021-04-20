if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

add_library(radlib "")

#################### Compile options

target_compile_features(radlib PUBLIC cxx_std_11)

set(CMAKE_CXX_FLAGS_DEBUG   "-ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#-------- create macro so that source code can access the rcslw data files
add_definitions(-DRCSLW_DATA_DIR=${INSTALLED_RCSLW_DATA_DIR})

#################### Local source files

target_sources(radlib PRIVATE
        rad.h
        rad_planck_mean.cc rad_planck_mean.h
        rad_wsgg.cc rad_wsgg.h
        rad_rcslw.cc rad_rcslw.h
        multilinear_interpolation.h
)

#################### installation

install(TARGETS radlib
        EXPORT radlibTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

FILE(GLOB_RECURSE radheaders "*.h")
install(FILES ${radheaders} DESTINATION include)

install(EXPORT radlibTargets
        FILE radlib.cmake
        NAMESPACE radlib::
        DESTINATION cmake/radlib
        )