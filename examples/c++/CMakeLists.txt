add_executable(simple_interface.x)
target_compile_features(   simple_interface.x PUBLIC cxx_std_11)
target_sources(            simple_interface.x PRIVATE simple_interface.cc)
target_include_directories(simple_interface.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     simple_interface.x radlib)

add_executable(ex_S1.x)
target_compile_features(   ex_S1.x PUBLIC cxx_std_11)
target_sources(            ex_S1.x PRIVATE ex_S1.cc parallel_planes.cc)
target_include_directories(ex_S1.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     ex_S1.x radlib)

add_executable(ex_S2.x)
target_compile_features(   ex_S2.x PUBLIC cxx_std_11)
target_sources(            ex_S2.x PRIVATE ex_S2.cc parallel_planes.cc)
target_include_directories(ex_S2.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     ex_S2.x radlib)

add_executable(ex_S3.x)
target_compile_features(   ex_S3.x PUBLIC cxx_std_11)
target_sources(            ex_S3.x PRIVATE ex_S3.cc parallel_planes.cc)
target_include_directories(ex_S3.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     ex_S3.x radlib)

add_executable(ex_S4.x)
target_compile_features(   ex_S4.x PUBLIC cxx_std_11)
target_sources(            ex_S4.x PRIVATE ex_S4.cc parallel_planes.cc)
target_include_directories(ex_S4.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     ex_S4.x radlib)

add_executable(ex_S5.x)
target_compile_features(   ex_S5.x PUBLIC cxx_std_11)
target_sources(            ex_S5.x PRIVATE ex_S5.cc parallel_planes.cc)
target_include_directories(ex_S5.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     ex_S5.x radlib)

add_executable(ex_B3.x)
target_compile_features(   ex_B3.x PUBLIC cxx_std_11)
target_sources(            ex_B3.x PRIVATE ex_B3.cc parallel_planes.cc)
target_include_directories(ex_B3.x PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../../source/c++)
target_link_libraries(     ex_B3.x radlib)

install(TARGETS simple_interface.x
                ex_S1.x 
                ex_S2.x 
                ex_S3.x 
                ex_S4.x 
                ex_S5.x 
                ex_B3.x 
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})
