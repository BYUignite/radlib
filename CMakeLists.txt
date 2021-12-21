################### PREAMBLE ###############################

cmake_minimum_required(VERSION 3.15)

project(radlib VERSION 2.0.0
        LANGUAGES CXX)

################### PROJECT-WIDE SETUP #######################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

# ---- set C++ language standard ----
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)

# ---- installation location ----
set(CMAKE_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}")

# ---- interface options ----
option(BUILD_PYTHON_INTERFACE   "build python interface" OFF)
option(BUILD_FORTRAN_INTERFACE  "build fortran interface" OFF)

# ---- options to build examples ----
option(BUILD_CXX_EXAMPLES       "Build C++ examples" OFF)
option(BUILD_PYTHON_EXAMPLES    "Build Python examples" OFF)
option(BUILD_FORTRAN_EXAMPLES   "Build Fortran examples" OFF)

# ---- option to build documentation ----
option(BUILD_DOCS "Build radlib docs" OFF)

################### MAIN PROJECT TARGETS #####################

# -------- RCSLW data library --------
get_filename_component(INSTALLED_RCSLW_DATA_DIR "${PROJECT_SOURCE_DIR}/data/rcslw_data" ABSOLUTE)
add_subdirectory(data/rcslw_data)

# -------- C++ executable --------
add_subdirectory(src/c++)

################### OPTIONAL PROJECT TARGETS #################

# -------- C++ EXAMPLES --------
if (BUILD_CXX_EXAMPLES)
    add_subdirectory(examples/c++)
endif()

# -------- PYTHON INTERFACE + EXAMPLES --------
if (BUILD_PYTHON_INTERFACE)
    add_subdirectory(src/python)
    if (BUILD_PYTHON_EXAMPLES)
        add_subdirectory(examples/python)
    endif()
endif()

# -------- FORTRAN INTERFACE + EXAMPLES --------
if (BUILD_FORTRAN_INTERFACE)
    enable_language(Fortran)
    add_subdirectory(src/fortran)
    if (BUILD_FORTRAN_EXAMPLES)
        add_subdirectory(examples/fortran)
    endif()
endif()

# -------- DOCUMENTATION --------
if (BUILD_DOCS)
    add_subdirectory(docs)
endif()