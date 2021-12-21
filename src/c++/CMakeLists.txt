############# RADPROPS LIBRARY ################

# -------- library targets --------
add_library(radProps rad.h
                     rad_planck_mean.cc rad_planck_mean.h
                     rad_wsgg.cc rad_wsgg.h
                     rad_rcslw.cc rad_rcslw.h
                     multilinear_interpolation.h)
add_library(radlib::radProps ALIAS radProps)    # alias for use as imported target

# -------- target properties --------
target_compile_features(radProps PUBLIC cxx_std_11)
set_target_properties(radProps PROPERTIES PUBLIC_HEADER "rad.h;rad_planck_mean.h;rad_rcslw.h;rad_wsgg.h;multilinear_interpolation.h")

# -------- dependencies --------
target_link_libraries(radProps PRIVATE RCSLW_data)

# -------- allows c++ code to access rcslw data --------
add_definitions(-DRCSLW_DATA_DIR=${INSTALLED_RCSLW_DATA_DIR})

############# LIBRARY INSTALLATION ################

include(GNUInstallDirs)

#---- allow radlib to be used in other targets ----
target_include_directories(radProps
        INTERFACE
            "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
        )

install(TARGETS radProps RCSLW_data
        EXPORT  radlib
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
        )

install(EXPORT radlib
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/radlib
        NAMESPACE radlib::
        )