from setuptools import setup
from Cython.Build import cythonize
import numpy as np

setup(
    ext_modules = cythonize("/Users/dol4/codes/radlib/examples/python/cyparallel_planes.pyx", language_level="3", annotate=False),
    include_dirs=[np.get_include()]
)

