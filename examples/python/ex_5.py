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
L      = 2.0
nGG    = 25
ntheta = 101
nx     = 1001
T0     = 1500.0
TL     = 500.0

nGGa   = nGG+1

TT = 1500; xco2=0.0; xco=0.0; xh2o=0.1; fvs=0.0

#---------------------

xCO2   = np.full(nx, xco2)
xCO    = np.full(nx, xco)
xH2O   = np.full(nx, xh2o)
xCH4   = np.full(nx, 0.0)
fvsoot = np.full(nx, fvs)

x = np.zeros(nx)
T = np.full(nx,T0)

dx = L/(nx-1)
x[0] = 0.0
Tavg = T[0]
for i in range(1,nx):
    x[i] = x[i-1] + dx
    T[i] = 1000.0 + 500*np.cos(np.pi*x[i]/L)
    Tavg += T[i]
Tavg /= nx

#rcslw = rad_rcslw(nGG, P, Tavg, xh2o, xco2, xco, fvs)  # TT gives better results than Tavg
rcslw = rad_rcslw(nGG, P, TT, xh2o, xco2, xco, fvs)  # TT gives better results than Tavg

#------------------- get q, Q

x, xQ, q, Q = parallel_planes(rcslw, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot)

print("# x (m), Q (kW/m3)")
for i in range(len(xQ)):
    print(f'{xQ[i]:.5f}  {Q[i]/1000:.5f}')

#print("# x (m), q (kW/m2)")
#for i in range(len(x)):
#    print(f'{x[i]:.5f}  {q[i]/1000:.5f}')

    #-------------------------------------------------------------------------

print()

