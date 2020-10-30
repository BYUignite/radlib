## Python examples 
* Python examples correspond to the c++ examples 
* These will import the pyrad library for the main radiation properties.
* The solver here is either parallel_planes.py or cyparallel_planes.pyx
* parallel_planes.py is pure python and is slow.
* cyparallel_planes.pyx is cython. Build it as:
    * ```python3 setup.py build_ext --inplace```  
    * This this will create the cyparallel_planes library with can be imported and called from the examples.
    * That is the default and is assumed in the example codes ex_*.py
    * If you want to use parallel_planes.py instead, just switch comments at the top of the example files.
