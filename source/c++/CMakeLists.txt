
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

FILE(GLOB_RECURSE rcslw_data_files "${RCSLW_DATA_DIR}/*.txt" "${RCSLW_DATA_DIR}/README.md")
install(FILES ${rcslw_data_files} DESTINATION ${INSTALLED_RCSLW_DATA_DIR})

FILE(GLOB_RECURSE radheaders "*.h")
install(FILES ${radheaders} DESTINATION include)

#################### Doxygen documentation

find_package(Doxygen)
if(DOXYGEN_FOUND)
    message("made it: ${CMAKE_CURRENT_BINARY_DIR}")
    add_custom_target(doxygen 
        COMMENT "Building doxygen documentation"
        COMMAND rm -rf ../../docs/doxygen/html
        COMMAND mkdir  ../../docs/doxygen/html
        COMMAND doxygen -s ../../docs/Doxyfile
        #WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        VERBATIM
    )
else()
    message("Cannot build documentation because doxygen was not found")
endif()

