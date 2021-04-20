# Radiation property library

This code provides radiation absorption coefficients for gas mixtures in the context of global (e.g., weighted sum of gray gas) models.
* In particular, the code implement three radiation models:
    * Rank Correlated Spectral Line Weighted Sum of Gray Gas [(RCSLW)](http://dx.doi.org/10.1016/j.jqsrt.2017.01.034) model,
    * Weighted Sum of Gray Gases [(WSGG)](http://dx.doi.org/10.1016/j.combustflame.2014.03.013) model,
    * Planck mean [(PM)](http://dx.doi.org/10.1016/j.combustflame.2014.03.013) absorption coefficients.
* Soot is included in all three models.
* The RCSLW model can be used with arbitrary number of gray gases. The PM model assumes one *gas*, and the WSGG model assumes four gray gases and one clear gas.

The library is written in C++ and include C++ and Python interfaces. 
* Several example cases are shown with comparisons to line-by-line results.
* A simple, one-dimensional radiation solver is included to demonstrate the use of the library and to solve example cases.

## Documentation
Detailed code documentation is available [here](https://ignite.byu.edu/radlib_documentation).

## Video
A [video](https://youtu.be/eFYMa5AVobI) giving a demonstration of the download, build, install, and run is provided.

## Code Ocean capsule
A Code Ocean capsule is available [here](https://codeocean.com/capsule/0997975/tree). This capsule provides a self-contained, runnable environment from which to examine the code, required software, and examples.

## Directory structure
The following directories are included. Key files are also described.
* ```LICENCE```: Licence file
* ```README.md```: this readme file
* ```build```: directory from which to build the code
* ```source```: source code. Contains the ```CMakeLists.txt``` file and two subdirectories:
    * ```c++```: includes header and source files for the ```rad``` abstract base class upon which the three current models, ```rad_planck_mean```, ```rad_wsgg```, and ```rad_rcslw``` are built.
    * ```python```: includes the ```pyrad.pyx``` cython interface file and the ```setup.py.in``` file that cmake converts to a ```setup.py``` file that is used for building the python interface.
* ```data```: contains ALBDF data files for the RCSLW model.
* ```docs```: contains doxygen build files. When built, the ```index.html``` file will redirect to the built documentation in the ```doxygen/html``` folder. Current source code is available as noted above.
* ```examples```: folder containing examples for c++ and python interfaces, as noted in the two subdirectories. These are described in more detail in the Examples section below.

## Required software

The code is intended to be built on Linux and MacOS systems (or the Linux subsystem for Windows). The build directory includes a README file that describes the build and installation process. 

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

## Building and installing the library

First, edit the ```build/CMakeLists.txt``` file to set the installation location. By default, the library is installed to the ```installed``` folder at the top level of the directory structure. This file also contains options to build the python/cython interfaces (```ON``` by default), examples (```ON``` by default, and documentation (```OFF``` by default).  

To build the package, navigate to the ```build``` directory and run the following commands:
```
cmake .
make
make install
```
To build the documentation (optional), run ```make docs``` from the ```build``` directory or navigate to the ```docs``` directory and run Doxygen directly with ```doxygen Doxyfile```. 

## Examples
 
Examples are provided in the ```examples/c++``` and ```examples/python``` directories and can be built as part of the build/installation process above. The C++ example executables are generated within the ```examples/c++``` folder and can be run individually or as a set with the ```run_examples.sh``` script. The Python examples can be executed directly (e.g. ```python3 ex_S3.py```) or from within the provided Jupyter notebook, which demonstrates all of the examples and provides graphical results. The Jupyter notebook can also be accessed online [here](https://github.com/BYUignite/radlib/blob/master/examples/python/run_and_plot_examples.ipynb).

## Acknowledgements
We gratefully acknowledge support and helpful discussions of Vladimir Solovjov on the RCSLW model, and Hadi Bordbar on the WSGG model.
