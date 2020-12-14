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

## Required software, building, and installing the library

The code is intended to be built on Linux and MacOS systems, (or the Linux subsystem for Windows). The build directory includes a readme file that describes the build and installation process.     Required software includes:
* CMake and a C++ compiler,
* Doxygen and graphviz to build the (optional) documentation,
* Python 3 and Cython to build the (optional) Python interface,
* Matplotlib, Numpy, and Jupyter (optional) to run the Python examples.

To build the code, the user edits the ```build/user_config``` file to set the installation location, and a flag indicating if the Python interface is to be built (on by default). The default       installation location is ```radlib/installed```. The ommands run are
```
cmake -C user_config ../source
make
make install
make doxygen
```

### Acknowledgements
We gratefully acknowledge support and helpful discussions of Vladimir
Solovjov on the RCSLW model, and Hadi Bordbar on the WSGG model.
