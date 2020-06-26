cmake_minimum_required(VERSION 3.12)
project(radlib LANGUAGES CXX C)

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
#set(CMAKE_CXX_FLAGS        "-Wall -Wextra")

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    target_link_libraries(radlib "-framework Accelerate")
endif()

#################### Local source files

target_sources(radlib
    PRIVATE
        rad.h
        rad_planck_mean.cc           rad_planck_mean.h
        rad_wsgg.cc                  rad_wsgg.h
        rad_rcslw.cc                 rad_rcslw.h
        multilinear_interpolation.h
)

#################### 

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)

#################### create macro so that source code can access the rcslw data files

set(RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/lib/rcslw_data")
add_definitions(-DRCSLW_DATA_DIR=${RCSLW_DATA_DIR})

#################### installation

install(TARGETS radlib 
        LIBRARY DESTINATION lib)

FILE(GLOB_RECURSE rcslw_data_files "rcslw_data/*.txt" "rcslw_data/README")
install(FILES ${rcslw_data_files} DESTINATION "lib/rcslw_data")

FILE(GLOB_RECURSE radheaders "*.h")
install(FILES ${radheaders} DESTINATION include)

#################### Doxygen documentation

find_package(Doxygen)
if(DOXYGEN_FOUND)
    add_custom_target(doxygen 
        COMMAND rm -rf ../docs/doxygen/html
        COMMAND mkdir  ../docs/doxygen/html
        COMMAND doxygen -s ../docs/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Building doxygen documentation"
        VERBATIM
    )
else()
    message("Cannot build documentation because doxygen was not found")
endif()

