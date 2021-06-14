## Building RadLib

------------------------------------------------------------------
### Dependencies

The code is intended to be built on Linux and MacOS systems (or the Linux subsystem for Windows).

Required software:
* CMake 3.15+

Optional software and Python packages for building the Python interface:
* Python 3.x
* Cython 0.29.21
* distutils
* numpy
* glob

Optional Python packages for running the Python examples
* matplotlib
* numpy
* Jupyter

Optional software for building documentation:
* Doxygen
* graphviz

------------------------------------------------------------------
### Build instructions

1. Create a directory ```build``` and navigate to it.
2. Run CMake: ```cmake ..```
3. Build radlib: ```make```
4. Install radlib: ```make install```
5. (OPTIONAL) Build documentation: ```make docs```
6. (CLEANUP) Clean build files: run ```git clean -d -f -x``` from top-level directory

------------------------------------------------------------------
### Default installation locations

* C++ library file ```libradlib.a``` located in ```installed/lib``` by default
* C++ header files located in ```installed/include``` by default
* Python package ```pyrad.so``` located in ```installed/lib/python_version/site-packages``` by default
* Relocatable package ```radlib.cmake``` located in ```installed/cmake/radlib``` by default
* Relocatable package ```radlib_fortran.cmake``` located in ```installed/cmake/radlib_fortran``` by default

