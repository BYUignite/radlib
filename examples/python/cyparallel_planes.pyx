
import  numpy as np
cimport numpy as np

ctypedef np.int_t INT
ctypedef np.float64_t FLOAT

cdef FLOAT sigma = 5.670367E-8     # Stephan-Boltzmann constant

cdef I_IT(np.ndarray[FLOAT, ndim=1] x,
          FLOAT                     theta, 
          np.ndarray[FLOAT, ndim=1] T,
          np.ndarray[FLOAT, ndim=2] kabs,
          np.ndarray[FLOAT, ndim=2] awts,
          np.ndarray[FLOAT, ndim=1] Ilo,
          np.ndarray[FLOAT, ndim=1] Ihi):
    '''
    Compute intensity at each grid point for a given angle.
    Solution using an implicit trapazoid method.
    @param x     \input vector of grid points
    @param theta \input angle measured: grid between plates aligned with theta=0
    @param T     \input vector of temperatures (K)
    @param kabs  \input 2D vector of absorption coefficients for each gas [igrid, igas]
    @param awts  \input 2D vector of weights for each gas [igrid, igas]
    @param Ilo   \input vector of gas intensities on the lower plane.
    @param Ihi   \input vector of gas intensities on the upper plane.
    @param I     \ouput vector of vector of gas intensities in direction theta [igrid, igas]
    '''

    cdef INT n     = len(x)
    cdef INT nGGa  = len(kabs[0,:])

    cdef np.ndarray[FLOAT, ndim=2] I = np.empty((n, nGGa), dtype=np.float64)

    cdef FLOAT Ib1, Ib2, dx
    cdef FLOAT mu = np.abs(np.cos(theta))

    cdef int i,j

    if(theta <= np.pi/2):
        I[0] = Ilo
        for i in range(n-1):     
            Ib1 = sigma/np.pi*T[i+1]**4
            Ib2 = sigma/np.pi*T[i]**4
            dx  = x[i+1] - x[i]
            #I[i+1,0] = I[0,0]           # do the clear gas intensity
            #for j in range(1,nGGa):
            for j in range(0,nGGa):      # OR, just do all (needed for Planck mean)     
                I[i+1,j] = (I[i,j] + dx/mu*0.5*(kabs[i+1,j]*awts[i+1,j]*Ib1 + kabs[i,j]*(awts[i,j]*Ib2 - I[i,j]))) / (1.0+dx/mu*0.5*kabs[i+1,j])
    else:
        I[n-1] = Ihi
        for i in range(n-1,0,-1):
            Ib1 = sigma/np.pi*T[i-1]**4
            Ib2 = sigma/np.pi*T[i]**4
            dx  = x[i] - x[i-1]
            #I[i-1,0] = I[n-1,0]         # do the clear gas intensity
            #for j in range(1,nGGa):
            for j in range(0,nGGa):      # OR, just do all (needed for Planck mean)
                I[i-1,j] = (I[i,j] + dx/mu*0.5*(kabs[i-1,j]*awts[i-1,j]*Ib1 + kabs[i,j]*(awts[i,j]*Ib2 - I[i,j]))) / (1.0+dx/mu*0.5*kabs[i-1,j])

    return I

################################################################################

def parallel_planes(                          RAD,
                    FLOAT                     L,
                    INT                       ntheta, 
                    FLOAT                     P, 
                    np.ndarray[FLOAT, ndim=1] T,
                    np.ndarray[FLOAT, ndim=1] xH2O,
                    np.ndarray[FLOAT, ndim=1] xCO2,
                    np.ndarray[FLOAT, ndim=1] xCO,
                    np.ndarray[FLOAT, ndim=1] xCH4,
                    np.ndarray[FLOAT, ndim=1] fvsoot,
                    bint                      LzeroIbc = False):
    '''
    Compute radiative heat flux (q) and volumetric heat source (Q) profiles between parallel planes.
    Solution using simple ray tracing.
    Pass in T, P, composition profiles on equally spaced points including boundaries.
    @param RAD      \input radlib object
    @param L        \input distance (m) between planes
    @param ntheta   \input number of ray angles
    @param P        \input system pressure (Pa)
    @param T        \input vector of temperatures at each point (K)
    @param xH2O     \input vector of H2O mole fractions at each point
    @param xCO2     \input vector of CO2 mole fractions at each point
    @param xCO      \input vector of CO  mole fractions at each point
    @param xCH4     \input vector of CH4 mole fractions at each point
    @param fvsoot   \input vector of soot volume fractions at each point
    @param q        \output vector of heat fluxes at each point (W/m2)
    @param x        \output vector of grid locations (m)
    @param xQ       \output vector of Q grid locations (m)
    @param LzeroIbc \input bool true to make Ibc=0, false otherwise (default = false)
     '''

    #--------------------- set the grid of x and array of theta

    cdef FLOAT dtheta = np.pi/ntheta

    cdef np.ndarray[FLOAT, ndim=1] theta = np.linspace(dtheta/2, np.pi-dtheta/2, ntheta, dtype=np.float64) 

    cdef int      nx = len(T)
    cdef FLOAT    dx = L/(nx-1)
    cdef np.ndarray[FLOAT, ndim=1] x  = np.linspace(0,L,nx, dtype=np.float64)   # x grid are face values:   |   |   |   |   | 
    cdef np.ndarray[FLOAT, ndim=1] xQ = 0.5*(x[:-1] + x[1:])   # xQ grid are cell centers:   *   *   *   *

    #--------------------- initialize radiative properties

    cdef np.ndarray[FLOAT, ndim=2] kabs = np.empty((nx, RAD.get_nGGa()), dtype=np.float64)
    cdef np.ndarray[FLOAT, ndim=2] awts = np.empty_like(kabs, dtype=np.float64)

    cdef int i,j
    cdef np.ndarray[FLOAT, ndim=1] Ilo, Ihi

    for i in range(nx):
        kabs[i,:], awts[i,:] = RAD.get_k_a(T[i], P, xH2O[i], xCO2[i], xCO[i], xCH4[i], fvsoot[i])

    if LzeroIbc:
        Ilo = np.zeros(RAD.get_nGGa())
        Ihi = np.zeros(RAD.get_nGGa())
    else:
        Ilo = sigma/np.pi*T[0] **4*awts[0,:]
        Ihi = sigma/np.pi*T[-1]**4*awts[-1,:]

    #--------------------- solve for q, Q

    cdef np.ndarray[FLOAT, ndim=1] q = np.zeros(nx,   dtype=np.float64)
    cdef np.ndarray[FLOAT, ndim=1] Q = np.empty(nx-1, dtype=np.float64)
    cdef np.ndarray[FLOAT, ndim=2] I

    for j in range(ntheta):
        I = I_IT(x, theta[j], T, kabs, awts, Ilo, Ihi)
        for i in range(nx):
            q[i] += 2.0*np.pi*dtheta*np.cos(theta[j])*np.sin(theta[j])*np.sum(I[i,:])

    Q = -(q[1:]-q[:-1])/dx

    return x, xQ, q, Q

