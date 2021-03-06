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
    * ```user_config```: user configurations; edit this file before building the code, see below.
* ```source```: source code. Contains the ```CMakeLists.txt``` file and two subdirectories:
    * ```c++```: includes header and source files for the ```rad``` abstract base class upon which the three current models, ```rad_planck_mean```, ```rad_wsgg```, and ```rad_rcslw``` are built.
    * ```python```: includes the ```pyrad.pyx``` cython interface file and the ```setup.py.in``` file that cmake converts to a ```setup.py``` file that is used for building the python interface.
* ```data```: contains ALBDF data files for the RCSLW model.
* ```docs```: contains doxygen build files. When built, the ```index.html``` file will redirect to the built documentation in the ```doxygen/html``` folder. Current source code is available as noted above.
* ```examples```: folder containing examples for c++ and python interfaces, as noted in the two subdirectories. These are described in more detail in the Examples section below.

## Required software

The code is intended to be built on Linux and MacOS systems, (or the Linux subsystem for Windows). The build directory includes a readme file that describes the build and installation process.     Required software includes:
* CMake and a C++ compiler,
* Doxygen and graphviz to build the (optional) documentation,
* Python 3 and Cython to build the (optional) Python interface,
* Matplotlib, Numpy, and Jupyter (optional) to run the Python examples.

## Building and installing the library

To build the code, the user edits the ```build/user_config``` file to set the installation location, and a flag indicating if the Python interface is to be built (on by default). The default installation location is ```radlib/installed```. The ommands run are
```
cmake -C user_config ../source
make
make install
make doxygen
```

## Examples
 
Examples are provided in the ```examples/c++``` and ```examples/python``` directories. 
* For C++, the examples codes are built as part of the build/installtion process, but there is also a script ```make_examples.sh``` the build the examples from the source. The examples are then executables that can be run. There is another script to run through all of the examples. The output is simple text written to the screen. The examples are repeated in Python, and graphical results are included there.
* For Python, the same examples are provided in two formats: (1) individual python files that can be executed as, e.g., ```python3 ex_S3.py```. There is also a Jupyter notebook that demonstrates the running of all examples and provides graphical results.
    * Here's a [link](https://github.com/BYUignite/radlib/blob/master/examples/python/run_and_plot_examples.ipynb) to the to the notebook.

## Acknowledgements
We gratefully acknowledge support and helpful discussions of Vladimir
Solovjov on the RCSLW model, and Hadi Bordbar on the WSGG model.
