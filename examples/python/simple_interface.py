##
# @file simple_interface.py
# \brief Simple interface: demonstrate calling library for one gas state
#

import numpy as np
import sys

sys.path.append('/Users/dol4/codes/radlib/installed/lib/python3.8/site-packages')

from pyrad import pyrad_planck_mean as rad_planck_mean
from pyrad import pyrad_wsgg        as rad_wsgg
from pyrad import pyrad_rcslw       as rad_rcslw

#--------------------------------------------------------------------------------

#----------------- define parameters

T      = 2000.0     # K
P      = 101325.0   # atm
xH2O   = 0.8        # xH2O=0.2 is roughly stoich. CH4/air products
xCO2   = 0.2        # xCO2=0.1 is roughly stoich. CH4/air products
xCO    = 0.0
xCH4   = 0.0
fvsoot = 0.0

#----------------- create radiation objects

planckmean = rad_planck_mean()
wsgg       = rad_wsgg()
rcslw      = rad_rcslw(4, T, P, fvsoot, xH2O, xCO2, xCO)

#----------------- compute absorption coefficients and weights

kabs_pm,    awts_pm     = planckmean.get_k_a(T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
kabs_wsgg,  awts_wsgg   = wsgg.get_k_a(      T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
kabs_rcslw, awts_rcslw  = rcslw.get_k_a(     T, P, fvsoot, xH2O, xCO2, xCO, xCH4)

#----------------- output results

print()
print(f"T (K)  = {T:14.3f}")
print(f"P (Pa) = {P:14.3f}")
print(f"xH2O   = {xH2O:14.3f}")
print(f"xCO2   = {xCO2:14.3f}")
print(f"xCO    = {xCO:14.3f}")
print(f"xCH4   = {xCH4:14.3f}")

print()
print("Planck Mean:")
print("   kabs (1/m),   awts")
for i in range(len(kabs_pm)):
    print(f"{kabs_pm[i]:14.8f}{awts_pm[i]:14.8f}")

print()
print("WSGG:")
print("   kabs (1/m),   awts")
for i in range(len(kabs_wsgg)):
    print(f"{kabs_wsgg[i]:14.8f}{awts_wsgg[i]:14.8f}")

print()
print("RCSLW:")
print("   kabs (1/m),   awts")
for i in range(len(kabs_rcslw)):
    print(f"{kabs_rcslw[i]:14.8f}{awts_rcslw[i]:14.8f}")
