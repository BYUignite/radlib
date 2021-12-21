# Building RadLib

------------------------------------------------------------------
## Dependencies

The code is intended to be built on Linux and Linux-like systems (MacOS, Windows Subsystem for Linux).

Required software:
* CMake 3.15 or higher
* C++11 or higher

Optional software and Python packages for building the Python interface:
* Python 3.x
* Cython 0.29.21
* distutils
* numpy
* glob

Optional Python packages for running the Python examples:
* matplotlib
* numpy
* Jupyter

Optional software for building the Fortran interface:
* gfortran (or another fortran compiler of your choice)

Optional software for building documentation:
* Doxygen
* graphviz

------------------------------------------------------------------
## Build instructions

For building and installing from the command line:
1. Create a directory ```build``` and navigate into it
2. Run CMake: ```cmake ..```
3. Build radlib: ```make```
4. Install radlib: ```make install```
5. (OPTIONAL) Build documentation: ```make docs```
6. (CLEANUP) Clean build files: run ```git clean -d -f -x``` from top-level directory

### CMake configuration options
By default, only the base C++ implementation is built. Optional interfaces, code examples, and documentation can be built by changing any of the following options on the command line (i.e. `cmake .. -DBUILD_CXX_EXAMPLES`) or in the top-level CMakeLists.txt file. 
* `BUILD_PYTHON_INTERFACE = ON/OFF`
* `BUILD_FORTRAN_INTERFACE = ON/OFF`
* `BUILD_CXX_EXAMPLES = ON/OFF`
* `BUILD_PYTHON_EXAMPLES = ON/OFF`
* `BUILD_FORTRAN_EXAMPLES = ON/OFF`
* `BUILD_DOCS = ON/OFF`

------------------------------------------------------------------
## Default installation locations
By default, libraries and header files are installed with the following file names to the following locations. 

* C++
    * Library: `libradlib.a` &rarr; `lib`
    * Header files: `rad_planck_mean.h`, `rad_rcslw.h`, and `rad_wsgg.h` &rarr; `include`
* Fortran
    * library: `libradlib_fortran.a` &rarr; `lib`
    * module file: `rad_module.mod` &rarr; `include`
        * This is included is user code with the `use rad_module` statement
* Python
    * package `pyrad.cpython-38-darwin.so` &rarr; `lib/python3.8/site-packages`
      * Note that the actual file names may differ depending on your machine and Python installation
      * The Python package is included in user code with statements such as `from pyrad import prad_rcslw`
* CMake
    * Relocatable package `radlib.cmake` &rarr; `lib/cmake/radlib`
    * Relocatable package `radlib_fortran.cmake` &rarr; `lib/cmake/radlib_fortran`