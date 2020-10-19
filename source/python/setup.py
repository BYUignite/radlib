from distutils.core      import setup, Extension
from Cython.Distutils    import build_ext
from distutils.extension import Extension

sources_list = ['pyrad.pyx', '../c++/rad_planck_mean.cc', '../c++/rad_wsgg.cc', '../c++/rad_rcslw.cc']

setup(ext_modules=[Extension('pyrad', 
                             sources=sources_list,
                             language='c++',
                             extra_compile_args=['-std=c++11', '-O3', '-DRCSLW_DATA_DIR=../c++/rcslw_data'])],
                             cmdclass={'build_ext':build_ext})
