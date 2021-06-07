cmake_minimum_required(VERSION 3.15)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

############################### PROJECT OPTIONS ###############################

# ---- set installation location ----
set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/installed CACHE STRING "installation location")

# ---- interface options ----
option(BUILD_PYTHON_INTERFACE   "build python interface" ON)
option(BUILD_CYTHON_INTERFACE   "build python interface: cython" OFF)
option(BUILD_FORTRAN_INTERFACE  "build fortran interface" ON)

# ---- options to build examples ----
option(BUILD_CXX_EXAMPLES       "Build C++ examples" ON)
option(BUILD_PYTHON_EXAMPLES    "Build Python examples" ON)
option(BUILD_FORTRAN_EXAMPLES   "Build Fortran examples" ON)

# ---- option to build documentation ----
option(BUILD_DOCS "Build radlib docs" OFF)

############################### RADLIB ###############################

project(radlib
        VERSION 1.0
        LANGUAGES CXX Fortran)

add_subdirectory(src/c++ ${CMAKE_CURRENT_BINARY_DIR}/src/c++)

# ------------- RCSLW data files -----------------
get_filename_component(INSTALLED_RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/rcslw_data" ABSOLUTE)
add_subdirectory(data/rcslw_data ${CMAKE_CURRENT_BINARY_DIR}/data/rcslw_data)

# ------------- PYTHON INTERFACE -----------------
if (BUILD_PYTHON_INTERFACE)
    add_subdirectory(src/python ${CMAKE_CURRENT_BINARY_DIR}/src/python)
endif()

# ------------- FORTRAN INTERFACE -----------------
if (BUILD_FORTRAN_INTERFACE)
    add_subdirectory(src/fortran ${CMAKE_CURRENT_BINARY_DIR}/src/fortran)
endif()

# ---- allow radlib to be used in other targets ----
target_include_directories(radlib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

############################### EXAMPLES ###############################

if (BUILD_CXX_EXAMPLES)
    add_subdirectory(examples/c++ ${CMAKE_CURRENT_BINARY_DIR}/examples/c++)
ENDIF()
if (BUILD_PYTHON_EXAMPLES AND BUILD_PYTHON_INTERFACE)
    add_subdirectory(examples/python ${CMAKE_CURRENT_BINARY_DIR}/examples/python)
endif()
if (BUILD_FORTRAN_EXAMPLES AND BUILD_FORTRAN_INTERFACE)
    add_subdirectory(examples/fortran ${CMAKE_CURRENT_BINARY_DIR}/examples/fortran)
endif()

############################### DOCUMENTATION ###########################

if (BUILD_DOCS)
    add_subdirectory(docs ${CMAKE_CURRENT_BINARY_DIR}/docs)
endif()
