##
# @file pyrad.pyx
# \brief cython file for Python interface to c++ code
#

from libcpp.vector cimport vector

import numpy as np

#================================================================================

cdef extern from "../c++/radPropModel.h":
    cdef cppclass radPropModel:
        radPropModel(int, int) except +
        int get_nGG()
        int get_nGGa()
        void get_k_a(vector[double]&, 
                     vector[double]&,
                     const double, 
                     const double, 
                     const double, 
                     const double, 
                     const double, 
                     const double, 
                     const double) 
        void get_k_a_oneband(double&, 
                             double&,
                             const int, 
                             const double, 
                             const double, 
                             const double, 
                             const double, 
                             const double, 
                             const double, 
                             const double) 

#--------------------------------------------------------------------------------

cdef extern from "../c++/rad_planck_mean.h":
    cdef cppclass rad_planck_mean(radPropModel):
        rad_planck_mean() except +

#--------------------------------------------------------------------------------

cdef extern from "../c++/rad_wsgg.h":
    cdef cppclass rad_wsgg(radPropModel):
        rad_wsgg() except +

#--------------------------------------------------------------------------------

cdef extern from "../c++/rad_rcslw.h":
    cdef cppclass rad_rcslw(radPropModel):
        rad_rcslw(const int,
                  const double,
                  const double,
                  const double,
                  const double,
                  const double,
                  const double) except +

#================================================================================

cdef class pyrad:

    cdef radPropModel *radptr

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
                double fvsoot,
                double xH2O,
                double xCO2,
                double xCO=0.0,
                double xCH4=0.0):
        
        cdef vector[double] kabs
        cdef vector[double] awts

        self.radptr.get_k_a(kabs, awts, T,P,fvsoot,xH2O,xCO2,xCO,xCH4)

        return np.array(kabs), np.array(awts)

    def get_k_a_oneband(self,
                        int    iband,
                        double T,
                        double P,
                        double fvsoot,
                        double xH2O,
                        double xCO2,
                        double xCO=0.0,
                        double xCH4=0.0):
        
        cdef double kabs
        cdef double awts

        self.radptr.get_k_a_oneband(kabs, awts, iband, T,P,fvsoot,xH2O,xCO2,xCO,xCH4)

        return kabs, awts

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
                  const double TbTref,
                  const double p_P,
                  const double fvsoot,
                  const double xH2O,
                  const double xCO2,
                  const double xCO):
        if type(self) is pyrad_rcslw:
            self.rad_rcslwptr = self.radptr = new rad_rcslw(p_nGG,TbTref,p_P,fvsoot,xH2O,xCO2,xCO)

    def __dealloc__(self):
        if type(self) is pyrad_rcslw:
            del self.rad_rcslwptr