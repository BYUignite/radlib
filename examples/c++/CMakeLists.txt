set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib") # to include sootlib (built in this project)
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)           # only needed if examples dep on an external lib

add_executable(            simple_interface.x simple_interface.cc)
target_include_directories(simple_interface.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     simple_interface.x radlib )
install(TARGETS            simple_interface.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_S1.x ex_S1.cc parallel_planes.cc)
target_include_directories(ex_S1.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_S1.x radlib)
install(TARGETS            ex_S1.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_S2.x ex_S2.cc parallel_planes.cc)
target_include_directories(ex_S2.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_S2.x radlib)
install(TARGETS            ex_S2.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_S3.x ex_S3.cc parallel_planes.cc)
target_include_directories(ex_S3.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_S3.x radlib)
install(TARGETS            ex_S3.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_S4.x ex_S4.cc parallel_planes.cc)
target_include_directories(ex_S4.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_S4.x radlib)
install(TARGETS            ex_S4.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_S5.x ex_S5.cc parallel_planes.cc)
target_include_directories(ex_S5.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_S5.x radlib)
install(TARGETS            ex_S5.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_B3.x ex_B3.cc parallel_planes.cc)
target_include_directories(ex_B3.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_B3.x radlib)
install(TARGETS            ex_B3.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(            ex_Sb1.x ex_Sb1.cc parallel_planes.cc)
target_include_directories(ex_Sb1.x PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
target_link_libraries(     ex_Sb1.x radlib)
install(TARGETS            ex_Sb1.x DESTINATION "${CMAKE_CURRENT_SOURCE_DIR}")
