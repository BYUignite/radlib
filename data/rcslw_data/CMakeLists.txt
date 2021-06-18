add_executable(writebin.x writebin.cc)

add_custom_command(TARGET writebin.x POST_BUILD
                   COMMAND writebin.x
                   COMMENT "\nWRITING BINARY RCSLW DATA FILES IN data/rcslw_data"
                   WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                   VERBATIM
                  )

install(FILES co2_p0_1.bin co2_p0_25.bin co2_p0_5.bin co2_p15_0.bin co2_p1_0.bin
              co2_p2_0.bin co2_p30_0.bin co2_p4_0.bin co2_p50_0.bin co2_p8_0.bin
              co_p0_1.bin  co_p0_25.bin  co_p0_5.bin  co_p15_0.bin  co_p1_0.bin
              co_p2_0.bin  co_p30_0.bin  co_p4_0.bin  co_p50_0.bin  co_p8_0.bin
              h2o_p0_1.bin h2o_p0_25.bin h2o_p0_5.bin h2o_p15_0.bin h2o_p1_0.bin
              h2o_p2_0.bin h2o_p30_0.bin h2o_p4_0.bin h2o_p50_0.bin h2o_p8_0.bin
              README.md
        DESTINATION "${INSTALLED_RCSLW_DATA_DIR}"
       )
