################################################################################

import numpy as np
from typing import Tuple, Any
from nptyping import NDArray

sigma = 5.670367E-8     # Stephan-Boltzmann constant

def I_IT(x:     NDArray[Any],
         theta: float, 
         T:     NDArray[Any],
         kabs:  NDArray[Any,Any],
         awts:  NDArray[Any,Any],
         Ilo:   NDArray[Any],
         Ihi:   NDArray[Any]) -> NDArray[Any,Any]:
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

    n     = len(x)
    nGGa  = len(kabs[0,:])

    mu = np.abs(np.cos(theta))

    I = np.empty((n, nGGa))

    if(theta <= np.pi/2):
        I[0] = Ilo
        for i in range(n-1):     
            Ib1 = sigma/np.pi*T[i+1]**4
            Ib2 = sigma/np.pi*T[i]**4
            dx  = x[i+1] - x[i]
            #I[i+1,0] = I[0,0]           # do the clear gas intensity
            #for j in range(1,nGGa):     # j=1 skips the clear gas, done in previous line
            for j in range(0,nGGa):      # OR, just do all (needed for Planck mean)     
                I[i+1,j] = (I[i,j] + dx/mu*0.5*(kabs[i+1,j]*awts[i+1,j]*Ib1 + kabs[i,j]*(awts[i,j]*Ib2 - I[i,j]))) / (1.0+dx/mu*0.5*kabs[i+1,j])
    else:
        I[n-1] = Ihi
        for i in range(n-1,0,-1):
            Ib1 = sigma/np.pi*T[i-1]**4
            Ib2 = sigma/np.pi*T[i]**4
            dx  = x[i] - x[i-1]
            #I[i-1,0] = I[n-1,0]         # do the clear gas intensity
            #for j in range(1,nGGa):     # j=1 skips the clear gas, done in previous line
            for j in range(0,nGGa):      # OR, just do all (needed for Planck mean)
                I[i-1,j] = (I[i,j] + dx/mu*0.5*(kabs[i-1,j]*awts[i-1,j]*Ib1 + kabs[i,j]*(awts[i,j]*Ib2 - I[i,j]))) / (1.0+dx/mu*0.5*kabs[i-1,j])

    return I

################################################################################

def parallel_planes(RAD,
                    L:        float,
                    ntheta:   int, 
                    P:        float, 
                    T:        NDArray[Any],
                    xH2O:     NDArray[Any],
                    xCO2:     NDArray[Any],
                    xCO:      NDArray[Any],
                    xCH4:     NDArray[Any],
                    fvsoot:   NDArray[Any],
                    LzeroIbc: bool = False) -> Tuple[NDArray[Any], NDArray[Any], NDArray[Any], NDArray[Any]]:
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

    dtheta = np.pi/ntheta

    theta = np.linspace(dtheta/2, np.pi-dtheta/2, ntheta) 

    nx = len(T)
    dx = L/(nx-1)
    x = np.linspace(0,L,nx)               # x grid are face values:   |   |   |   |   | 
    xQ = 0.5*(x[:-1] + x[1:])             # xQ grid are cell centers:   *   *   *   *

    #--------------------- initialize radiative properties

    kabs = np.empty((nx, RAD.get_nGGa()))
    awts = np.empty_like(kabs)

    for i in range(nx):
        kabs[i,:], awts[i,:] = RAD.get_k_a(T[i], P, xH2O[i], xCO2[i], xCO[i], xCH4[i], fvsoot[i])

    if LzeroIbc:
        Ilo = np.zeros(RAD.get_nGGa())
        Ihi = np.zeros(RAD.get_nGGa())
    else:
        Ilo = sigma/np.pi*T[0] **4*awts[0,:]
        Ihi = sigma/np.pi*T[-1]**4*awts[-1,:]

    #--------------------- solve for q, Q

    q = np.zeros(nx)
    Q = np.empty(nx-1)

    for j in range(ntheta):
        I = I_IT(x, theta[j], T, kabs, awts, Ilo, Ihi)
        for i in range(nx):
            q[i] += 2.0*np.pi*dtheta*np.cos(theta[j])*np.sin(theta[j])*np.sum(I[i,:])

    Q = -(q[1:]-q[:-1])/dx

    return x, xQ, q, Q

