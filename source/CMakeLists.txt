cmake_minimum_required(VERSION 3.10)
project(radlib LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(RCSLW_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../data/rcslw_data")
get_filename_component(INSTALLED_RCSLW_DATA_DIR "${CMAKE_INSTALL_PREFIX}/rcslw_data" ABSOLUTE)

add_subdirectory(c++)
add_subdirectory(python)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../examples/c++    ${CMAKE_CURRENT_BINARY_DIR}/examples/c++)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../examples/python ${CMAKE_CURRENT_BINARY_DIR}/examples/python)
