find_program(Julia_EXECUTABLE NAMES julia)

if(Julia_EXECUTABLE AND BUILD_JULIA_INTERFACE)
    
    set(CMAKE_PREFIX_PATH "/Users/dol4/.julia/artifacts/62eae10c647bb4ea186063b758bc3fc5881a34f1")
    find_package(JlCxx)
    
    add_library(radlib_julia SHARED radlib_julia.cc)
    
    target_include_directories(radlib_julia PRIVATE "${CMAKE_SOURCE_DIR}/src/c++" "${CMAKE_SOURCE_DIR}/data/rcslw_data")
    
    target_link_libraries(radlib_julia radlib JlCxx::cxxwrap_julia JlCxx::cxxwrap_julia_stl)

    install(FILES radlib.jl
            DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
           )

    install(TARGETS radlib_julia 
            EXPORT  radlib_juliaTargets
            LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
           )
    install(EXPORT radlib_juliaTargets
            FILE radlib_julia.cmake
            NAMESPACE radlib_julia::
            DESTINATION cmake/radlib_julia
           )

elseif(!Julia_EXECUTABLE AND BUILD_JULIA_INTERFACE)

    message([FATAL_ERROR] "Julia not found")

endif()
