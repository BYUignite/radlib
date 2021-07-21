# Building RadLib

------------------------------------------------------------------
## Dependencies

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
## Build instructions

1. Create a directory ```build``` and navigate to it.
2. Run CMake: ```cmake ..```
3. Build radlib: ```make```
4. Install radlib: ```make install```
5. (OPTIONAL) Build documentation: ```make docs```
6. (CLEANUP) Clean build files: run ```git clean -d -f -x``` from top-level directory

### Notes
* See the top of the root ```CMakeLists.txt``` file for build options.
* The code defaults to building the Python and Fortran interfaces, along with the C++, Python, and Fortran examples. The documentation build is off by default. These options can be changed in the CMakeLists.txt file, or at the command line. For example,
    * ```cmake -DBUILD_PYTHON_INTERFACE=OFF ..```

------------------------------------------------------------------
## Default installation locations

* C++
    * library: ```libradlib.a``` is located in ```installed/lib```
    * header files: ```rad_planck_mean.h```, ```rad_rcslw.h```, ```rad_wsgg.h``` are located in ```installed/include```
* Fortran
    * library: ```libradlib_fortran.a``` is located in ```installed/lib```
    * module file: ```rad_module.mod``` is located in ```installed/include```
        * This is included is user code with the ```use rad_module``` statement.
* Python
    * package ```pyrad.cpython-38-darwin.so``` is located in ```installed/lib/python3.8/site-       packages```. Note that the actual file names may differ depending on the machine and Python         installation.
        * The Python package is included in user code with statements such as ```from pyrad import  prad_rcslw```
* CMake
    * Relocatable package ```radlib.cmake``` is located in ```installed/cmake/radlib```
    * Relocatable package ```radlib_fortran.cmake``` located in ```installed/cmake/radlib_fortran```

