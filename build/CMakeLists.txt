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

# ---- option to cython interface ----
set(BUILD_CYTHON_INTERFACE     "YES"    CACHE STRING "build python interface: cython")

############################### RADLIB ###############################

project(radlib)

get_filename_component(INSTALLED_RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/rcslw_data" ABSOLUTE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../src/c++             ${CMAKE_CURRENT_BINARY_DIR}/src/c++)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../src/python          ${CMAKE_CURRENT_BINARY_DIR}/src/python)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../data/rcslw_data     ${CMAKE_CURRENT_BINARY_DIR}/data/rcslw_data)

# ---- allow rad to be used in other targets ----
target_include_directories(radlib PUBLIC ../src)

############################### EXAMPLES ###############################

if (BUILD_EXAMPLES)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../examples/c++    ${CMAKE_CURRENT_BINARY_DIR}/examples/c++)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../examples/python ${CMAKE_CURRENT_BINARY_DIR}/examples/python)
endif()

############################### DOCUMENTATION ###########################

if (BUILD_DOCS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../docs            ${CMAKE_CURRENT_BINARY_DIR}/docs)
endif()
