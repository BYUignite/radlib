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
L      = 1.0
nGG    = 24
ntheta = 101
nx     = 1001
Twall  = 800.0

nGGa   = nGG+1

xco2=0.0; xco=0.0; xh2o=0.12; xch4=0.0; fvs=0.0

#---------------------

xCO2   = np.full(nx, xco2)
xCO    = np.full(nx, xco)
xH2O   = np.full(nx, xh2o)
xCH4   = np.full(nx, xch4)
fvsoot = np.full(nx, fvs)

x = np.zeros(nx)
T = np.full(nx,Twall)

dx = L/(nx-1)
x[0] = 0.0
Tavg = T[0]
xH2O_avg = 0.0
for i in range(1,nx):
    x[i] = x[i-1] + dx
    T[i] = 4000*x[i]*(L-x[i])/L/L + Twall
    xH2O[i] = 0.8*x[i]*(L-x[i])/L/L + xh2o
    Tavg += T[i]
    xH2O_avg += xH2O[i]
Tavg     /= nx
xH2O_avg /= nx

rcslw = rad_rcslw(nGG, P, Tavg, xH2O_avg, xco2, xco, fvs)

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

