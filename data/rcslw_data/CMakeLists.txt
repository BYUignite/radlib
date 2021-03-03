add_executable(            writebin.x "")
target_compile_features(   writebin.x PUBLIC cxx_std_11)
target_sources(            writebin.x PRIVATE writebin.cc)

install(TARGETS writebin.x
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

install(CODE "execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/writebin.x
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})")
#install(CODE "execute_process(COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/writebin.x)"
#    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB_RECURSE rcslw_data_files "*.bin" "README.md")
install(FILES ${rcslw_data_files} DESTINATION ${INSTALLED_RCSLW_DATA_DIR})
