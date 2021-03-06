## Building radlib source code with cmake

------------------------------------------------------------------
### SOFTWARE 

* Required software:
    * cmake (3.12 or higher)

* Optional software:
    * doxygen (for building documentation)

------------------------------------------------------------------
### Build instructions 

* STEP 1: run cmake
    * Edit the user_config file for settings and paths.
    * RUN: `cmake -C user_config ../source/`

* STEP 2: build the radlib code
    * RUN: `make`

* STEP 3: install the code
    * RUN: `make install`

* STEP 4 (OPTIONAL):  build documentation
    * RUN: `make doxygen`
    
------------------------------------------------------------------

### Cleanup instructions 

* Basic cleanup:
    * RUN: `make clean`

* Thorough cleanup:
    * RUN: `./clean_this_dir.sh`

------------------------------------------------------------------

### Notes

* `CMakeLists.txt` files are located in `../source` directory and its subdirectories.
* All files in this build folder can be deleted except for user_config and this README.md.

