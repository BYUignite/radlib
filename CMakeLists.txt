cmake_minimum_required(VERSION 3.23)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

############################### PROJECT OPTIONS ###############################

#----- installation location
#----- cmake --install-prefix /opt/radlib ..
#----- or use this default:

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/installed" CACHE STRING "install location")

#----- options: interfaces, examples, documentation

option(BUILD_PYTHON_INTERFACE  "build python interface"  OFF)
option(BUILD_FORTRAN_INTERFACE "build fortran interface" OFF)

option(BUILD_CXX_EXAMPLES      "Build C++ examples"      OFF)
option(BUILD_PYTHON_EXAMPLES   "Build Python examples"   OFF)
option(BUILD_FORTRAN_EXAMPLES  "Build Fortran examples"  OFF)

option(BUILD_DOCS              "Build radlib docs"       OFF)

############################### RADLIB ###############################

project(radlib VERSION 1.0 LANGUAGES CXX)

# ------------- RCSLW data files

get_filename_component(INSTALLED_RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/rcslw_data" ABSOLUTE)
add_subdirectory(data/rcslw_data "${CMAKE_CURRENT_BINARY_DIR}/data/rcslw_data")

# ------------- C++ main code

add_subdirectory(src/c++)

# ------------- PYTHON INTERFACE

if(BUILD_PYTHON_INTERFACE)
    add_subdirectory(src/python)
endif()

# ------------- FORTRAN INTERFACE

if(BUILD_FORTRAN_INTERFACE)
    enable_language(Fortran)
    add_subdirectory(src/fortran)
endif()

############################### EXAMPLES ###############################

if(BUILD_CXX_EXAMPLES)
    add_subdirectory(examples/c++)
ENDIF()

if(BUILD_FORTRAN_EXAMPLES AND BUILD_FORTRAN_INTERFACE)
    add_subdirectory(examples/fortran)
endif()

if(BUILD_PYTHON_EXAMPLES AND BUILD_PYTHON_INTERFACE)
    add_subdirectory(examples/python)
endif()

############################### DOCUMENTATION ###########################

if(BUILD_DOCS)
    add_subdirectory(docs "${CMAKE_CURRENT_BINARY_DIR}/docs")
endif()
