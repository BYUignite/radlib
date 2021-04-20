## Building RadLib

------------------------------------------------------------------
### SOFTWARE 

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

1. Edit the ```build/CMakeLists.txt``` file for settings and paths.
2. Run CMake: ```cmake .```
3. Build the code: ```make```
4. Install the code: ```make install```
5. (OPTIONAL) Build the documentation: ```make docs```
    
------------------------------------------------------------------

### Cleanup instructions 

* Basic cleanup: ```make clean```
* Thorough cleanup: ```./clean_this_dir.sh```

------------------------------------------------------------------

### Notes

* `CMakeLists.txt` files are located in the ```src``` directory and its subdirectories.
* All files in this build folder can be deleted except for ```CMakeLists.txt```, ```clean_this_dir.sh```, and this ```README.md```.

