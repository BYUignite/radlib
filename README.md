# Radiation property library

* Provides radiation absorption coefficients for gas mixtures in the context of weighted sum of gray gas models. 
* In particular, the code is implemented for three radiation models:
    * Rank correlated spectral line weighted sum of gray gas model (RCSLW),
    * Weighted sum of gray gases model,
    * Planck mean absorption coefficients.
* Soot is included in the models.
* The RCSLW model can be used with arbitrary number of gray gases. The Planck mean model assumes one *gas*, and the WSGG model assumes four gases.

* The library is written in C++ and includes C++ and Python interfaces. 
* Several example cases are shown with comparisons to line-by-line data.
* A simple, one-dimensional radiation solver is included to demonstrate the use of the library and to solve example cases.
