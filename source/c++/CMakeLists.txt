
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

add_library(radlib "")
#target_include_directories(radlib PRIVATE .)

set(CMAKE_VERBOSE_MAKEFILE ON)

#################### Compile options

target_compile_features(radlib PUBLIC cxx_std_11)

set(CMAKE_CXX_FLAGS_DEBUG   "-ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

#-------- create macro so that source code can access the rcslw data files
add_definitions(-DRCSLW_DATA_DIR=${INSTALLED_RCSLW_DATA_DIR})

#################### Local source files

target_sources(radlib
    PRIVATE
        rad.h
        rad_planck_mean.cc           rad_planck_mean.h
        rad_wsgg.cc                  rad_wsgg.h
        rad_rcslw.cc                 rad_rcslw.h
        multilinear_interpolation.h
)

#################### installation

install(TARGETS radlib 
        LIBRARY DESTINATION lib)

FILE(GLOB_RECURSE radheaders "*.h")
install(FILES ${radheaders} DESTINATION include)

