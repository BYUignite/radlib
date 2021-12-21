############# C++ EXAMPLES ################

add_executable(simple_interface simple_interface.cc)
target_link_libraries(simple_interface radProps)

add_executable(ex_S1 ex_S1.cc parallel_planes.cc)
target_link_libraries(ex_S1 radProps)

add_executable(ex_S2 ex_S2.cc parallel_planes.cc)
target_link_libraries(ex_S2 radProps)

add_executable(ex_S3 ex_S3.cc parallel_planes.cc)
target_link_libraries(ex_S3 radProps)

add_executable(ex_S4 ex_S4.cc parallel_planes.cc)
target_link_libraries(ex_S4 radProps)

add_executable(ex_S5 ex_S5.cc parallel_planes.cc)
target_link_libraries(ex_S5 radProps)

add_executable(ex_B3 ex_B3.cc parallel_planes.cc)
target_link_libraries(ex_B3 radProps)

add_executable(ex_Sb1 ex_Sb1.cc parallel_planes.cc)
target_link_libraries(ex_Sb1 radProps)

install(TARGETS simple_interface ex_S1 ex_S2 ex_S3 ex_S4 ex_S5 ex_B3 ex_Sb1
        DESTINATION "${CMAKE_CURRENT_LIST_DIR}")