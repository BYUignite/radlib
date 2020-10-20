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
rcslw      = rad_rcslw(4, P, T, xH2O, xCO2, xCO, fvsoot)

#----------------- compute absorption coefficients and weights

kabs_pm,    awts_pm     = planckmean.get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
kabs_wsgg,  awts_wsgg   = wsgg.get_k_a(      T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
kabs_rcslw, awts_rcslw  = rcslw.get_k_a(     T, P, xH2O, xCO2, xCO, xCH4, fvsoot)

#----------------- output results

print(f"---------------------------")
print(f"T (K)  = {T:.3f}")
print(f"P (Pa) = {P:.3f}")
print(f"xH2O   = {xH2O:.3f}")
print(f"xCO2   = {xCO2:.3f}")
print(f"xCO    = {xCO:.3f}")
print(f"xCH4   = {xCH4:.3f}")

print(f"---------------------------")
print("Planck Mean:")
print(f"   kabs (1/m) = ", end='')
for i in range(len(kabs_pm)):
    print(f"{kabs_pm[i]:12.3e}", end='\n' if i==len(kabs_pm)-1 else ',')  
print(f"   awts       = ", end='')
for i in range(len(awts_pm)):
    print(f"{awts_pm[i]:12.3e}", end='\n' if i==len(awts_pm)-1 else ',')  

print(f"---------------------------")
print("WSGG:")
print(f"   kabs (1/m) = ", end='')
for i in range(len(kabs_wsgg)):
    print(f"{kabs_wsgg[i]:12.3e}", end='\n' if i==len(kabs_wsgg)-1 else ',')  
print(f"   awts       = ", end='')
for i in range(len(awts_wsgg)):
    print(f"{awts_wsgg[i]:12.3e}", end='\n' if i==len(awts_wsgg)-1 else ',')  

print(f"---------------------------")
print("RCSLW:")
print(f"   kabs (1/m) = ", end='')
for i in range(len(kabs_rcslw)):
    print(f"{kabs_rcslw[i]:12.3e}", end='\n' if i==len(kabs_rcslw)-1 else ',')  
print(f"   awts       = ", end='')
for i in range(len(awts_rcslw)):
    print(f"{awts_rcslw[i]:12.3e}", end='\n' if i==len(awts_rcslw)-1 else ',')  
