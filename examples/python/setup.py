from setuptools import setup
from Cython.Build import cythonize
import numpy as np

setup(
    ext_modules = cythonize("cyparallel_planes.pyx", language_level="3", annotate=False),
    include_dirs=[np.get_include()]
)
