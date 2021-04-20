cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 11)

############################### PROJECT OPTIONS ###############################

# ---- set installation location ----
#set(CMAKE_INSTALL_PREFIX "/Users/yourUserName/Desktop" CACHE STRING "installation location: comment this out to use the default")
set(CMAKE_INSTALL_PREFIX "../installed" CACHE STRING "installation location: comment this out to use the default")

# ---- option to build examples ----
option(BUILD_EXAMPLES "Build radlib examples" ON)

# ---- option to build documentation ----
option(BUILD_DOCS "Build radlib docs" ON)

# ---- option to build cython interface ----
option(BUILD_CYTHON_INTERFACE "build python interface: cython" ON)

############################### RADLIB ###############################

project(radlib)

get_filename_component(INSTALLED_RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/rcslw_data" ABSOLUTE)

add_subdirectory(../src/c++ ${CMAKE_CURRENT_BINARY_DIR}/src/c++)
add_subdirectory(../src/python ${CMAKE_CURRENT_BINARY_DIR}/src/python)
add_subdirectory(../data/rcslw_data ${CMAKE_CURRENT_BINARY_DIR}/data/rcslw_data)

# ---- allow rad to be used in other targets ----
#target_include_directories(radlib PUBLIC ../src)
target_include_directories(radlib PUBLIC
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
        "$<INSTALL_INTERFACE:include>"
        )

############################### EXAMPLES ###############################

if (BUILD_EXAMPLES)
    add_subdirectory(../examples/c++ ${CMAKE_CURRENT_BINARY_DIR}/examples/c++)
    add_subdirectory(../examples/python ${CMAKE_CURRENT_BINARY_DIR}/examples/python)
endif()

############################### DOCUMENTATION ###########################

if (BUILD_DOCS)
    add_subdirectory(../docs ${CMAKE_CURRENT_BINARY_DIR}/docs)
endif()
