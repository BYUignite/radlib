cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build")

############################### PROJECT OPTIONS ###############################

# ---- set installation location ----
#set(CMAKE_INSTALL_PREFIX "/Users/yourUserName/Desktop" CACHE STRING "installation location: comment this out to use the default")
set(CMAKE_INSTALL_PREFIX "installed" CACHE STRING "installation location")

# ---- option to build python interface ----
option(BUILD_PYTHON_INTERFACE "build python interface" ON)

# ---- option to build cython interface ----
option(BUILD_CYTHON_INTERFACE "build python interface: cython" ON)

# ---- option to build examples ----
option(BUILD_EXAMPLES "Build radlib examples" ON)

# ---- option to build documentation ----
option(BUILD_DOCS "Build radlib docs" OFF)

############################### RADLIB ###############################

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)      # Release or Debug
endif()

project(radlib)

get_filename_component(INSTALLED_RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/rcslw_data" ABSOLUTE)

add_subdirectory(src/c++ ${CMAKE_CURRENT_BINARY_DIR}/src/c++)
add_subdirectory(data/rcslw_data ${CMAKE_CURRENT_BINARY_DIR}/data/rcslw_data)

if (BUILD_PYTHON_INTERFACE)
    add_subdirectory(src/python ${CMAKE_CURRENT_BINARY_DIR}/src/python)
endif()

# ---- allow radlib to be used in other targets ----
target_include_directories(radlib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

############################### EXAMPLES ###############################

if (BUILD_EXAMPLES)
    add_subdirectory(examples/c++ ${CMAKE_CURRENT_BINARY_DIR}/examples/c++)
    if (BUILD_PYTHON_INTERFACE)
        add_subdirectory(examples/python ${CMAKE_CURRENT_BINARY_DIR}/examples/python)
    endif()
endif()

############################### DOCUMENTATION ###########################

if (BUILD_DOCS)
    add_subdirectory(docs ${CMAKE_CURRENT_BINARY_DIR}/docs)
endif()
