##
# @file pyrad.pyx
# \brief cython file for Python interface to c++ code
#

from libcpp.vector cimport vector

import numpy as np

#================================================================================

cdef extern from "../c++/rad.h":
    cdef cppclass rad:
        rad(int, int) except +
        int get_nGG()
        int get_nGGa()
        void get_k_a(const double, 
                     const double, 
                     const double, 
                     const double, 
                     const double, 
                     const double, 
                     const double, 
                     vector[double]&, 
                     vector[double]&)

#--------------------------------------------------------------------------------

cdef extern from "../c++/rad_planck_mean.h":
    cdef cppclass rad_planck_mean(rad):
        rad_planck_mean() except +

#--------------------------------------------------------------------------------

cdef extern from "../c++/rad_wsgg.h":
    cdef cppclass rad_wsgg(rad):
        rad_wsgg() except +

#--------------------------------------------------------------------------------

cdef extern from "../c++/rad_rcslw.h":
    cdef cppclass rad_rcslw(rad):
        rad_rcslw(const int,
                  const double,
                  const double,
                  const double,
                  const double,
                  const double,
                  const double) except +

#================================================================================

cdef class pyrad:

    cdef rad *radptr

    def __cinit__(self): #, int nGG, int nGGa):
        pass

    def __dealloc__(self):
        if type(self) is pyrad:
            del self.radptr

    def get_nGG(self):
        return self.radptr.get_nGG()

    def get_nGGa(self):
        return self.radptr.get_nGGa()

    def get_k_a(self,
                double T,
                double P,
                double xH2O,
                double xCO2,
                double xCO,
                double xCH4,
                double fvsoot):
        
        cdef vector[double] kabs
        cdef vector[double] awts

        self.radptr.get_k_a(T,P,xH2O,xCO2,xCO,xCH4,fvsoot,  kabs,awts)

        return np.array(kabs), np.array(awts)

#--------------------------------------------------------------------------------

cdef class pyrad_planck_mean(pyrad):

    cdef rad_planck_mean *rad_planck_meanptr

    def __cinit__(self):
        if type(self) is pyrad_planck_mean:
            self.rad_planck_meanptr = self.radptr = new rad_planck_mean()

    def __dealloc__(self):
        if type(self) is pyrad_planck_mean:
            del self.rad_planck_meanptr

#--------------------------------------------------------------------------------

cdef class pyrad_wsgg(pyrad):

    cdef rad_wsgg *rad_wsggptr

    def __cinit__(self):
        if type(self) is pyrad_wsgg:
            self.rad_wsggptr = self.radptr = new rad_wsgg()

    def __dealloc__(self):
        if type(self) is pyrad_wsgg:
            del self.rad_wsggptr

#--------------------------------------------------------------------------------

cdef class pyrad_rcslw(pyrad):

    cdef rad_rcslw *rad_rcslwptr

    def __cinit__(self, 
                  const int    p_nGG,
                  const double p_P,
                  const double TbTref,
                  const double xH2O,
                  const double xCO2,
                  const double xCO,
                  const double fvsoot):
        if type(self) is pyrad_rcslw:
            self.rad_rcslwptr = self.radptr = new rad_rcslw(p_nGG,p_P,TbTref,xH2O,xCO2,xCO,fvsoot)

    def __dealloc__(self):
        if type(self) is pyrad_rcslw:
            del self.rad_rcslwptr

