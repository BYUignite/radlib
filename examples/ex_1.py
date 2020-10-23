import numpy as np
import sys

from parallel_planes import parallel_planes, sigma

sys.path.append('/Users/dol4/codes/radlib/installed/lib/python3.8/site-packages')

from pyrad import pyrad_planck_mean as rad_planck_mean
from pyrad import pyrad_wsgg        as rad_wsgg
from pyrad import pyrad_rcslw       as rad_rcslw

################################################################################

#--------------------- parameters

P      = 101325.0
Thot   = 2000
Tcold  = 300
Lhot   = 0.5
nGG    = 24
ntheta = 101
nxh    = 1001    # for Lcold=0 changes below to keep dx roughly constant

Lcold  = np.array([0, 0.01, 0.025, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.75, 1.0, 1.5, 2.0])

nGGa   = nGG+1

xco2=0.1; xco=0.0; xh2o=0.2; xch4=0.0; fvs=0.0

#---------------------

print("# Lcold (m), q(L)/σThot^4")

for iLcold in range(len(Lcold)):

    L  = Lcold[iLcold] + Lhot

    Tavg = (Thot*0.5+Tcold*Lcold[iLcold])/L

    nx = int(nxh*L/Lhot)

    xCO2   = np.full(nx, xco2)
    xCO    = np.full(nx, xco)
    xH2O   = np.full(nx, xh2o)
    xCH4   = np.full(nx, xch4)
    fvsoot = np.full(nx, fvs)

    x = np.zeros(nx)
    dx = L/(nx-1)
    T = np.full(nx, Thot)
    for i in range(1,nx):        # mimic c++; pythonic gives different grid/T due to roundoff
        x[i] = x[i-1] + dx
        T[i] = Thot if x[i] <= Lhot else Tcold


    rcslw = rad_rcslw(nGG, P, Tavg, xh2o, xco2, xco, fvs)

    #--------------------- get q, Q

    x, xQ, q, Q = parallel_planes(rcslw, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, True)

    #-------------------------------------------------------------------------

    print(f'{Lcold[iLcold]}  {q[nx-1]/sigma/Thot**4}')

print()

