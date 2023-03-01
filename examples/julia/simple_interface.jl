##
# @file simple_interface.jl
# \brief Simple interface: demonstrate calling library for one gas state
#

include("/Users/dol4/codes/radlib/installed/include/radlib.jl")

using .radlib
using CxxWrap

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

kabs_pm,    awts_pm    = StdVector(), StdVector()
kabs_wsgg,  awts_wsgg  = StdVector(), StdVector()
kabs_rcslw, awts_rcslw = StdVector(), StdVector()


get_k_a(pm,    kabs_pm,    awts_pm,    T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
get_k_a(wsgg,  kabs_wsgg,  awts_wsgg,  T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
get_k_a(rcslw, kabs_rcslw, awts_rcslw, T, P, fvsoot, xH2O, xCO2, xCO, xCH4)


# nGG  = get_nGG(wsgg)
# nGGa = get_nGGa(wsgg)
# println(nGG)
# println(nGGa)

