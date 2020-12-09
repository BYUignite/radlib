# Radiation property library

Provides radiation absorption coefficients for gas mixtures in the context of weighted sum of gray gas models. 
* In particular, the code implement three radiation models:
    * Rank Correlated Spectral Line Weighted Sum of Gray Gas (RCSLW) model,
    * Weighted Sum of Gray Gases (WSGG) model,
    * Planck mean (PM) absorption coefficients.
* Soot is included in the RCSLW and PM models.
* The RCSLW model can be used with arbitrary number of gray gases. The PM model assumes one *gas*, and the WSGG model assumes four gray gases.
* Note, a consistent interface is used for the various models, but not every parameter applies to every model (e.g., WSGG will take a soot parameter but it isn't used).

The library is written in C++ and include C++ and Python interfaces. 
* Several example cases are shown with comparisons to line-by-line results.
* A simple, one-dimensional radiation solver is included to demonstrate the use of the library and to solve example cases.

A [video](https://youtu.be/eFYMa5AVobI) giving a demonstration of the download, build, install, and run is provided.

### Acknowledgements
We gratefully acknowledge support and helpful discussions of Vladimir
Solovjov on the RCSLW model, and Hadi Bordbar on the WSGG model.
