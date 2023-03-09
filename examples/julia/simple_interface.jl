##
# @file simple_interface.jl
# \brief Simple interface: demonstrate calling library for one gas state
#

include("/Users/dol4/codes/radlib/installed/include/radlib.jl")

using .radlib
using CxxWrap
using Printf

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

kabs_pm,    awts_pm    = StdVector(zeros(get_nGGa(planckmean))), StdVector(zeros(get_nGGa(planckmean)))
kabs_wsgg,  awts_wsgg  = StdVector(zeros(get_nGGa(wsgg))),       StdVector(zeros(get_nGGa(wsgg)))
kabs_rcslw, awts_rcslw = StdVector(zeros(get_nGGa(rcslw))),      StdVector(zeros(get_nGGa(rcslw)))

get_k_a(planckmean, kabs_pm,    awts_pm,    T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
get_k_a(wsgg,       kabs_wsgg,  awts_wsgg,  T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
get_k_a(rcslw,      kabs_rcslw, awts_rcslw, T, P, fvsoot, xH2O, xCO2, xCO, xCH4)

#----------------- output results

println()
@printf("T (K)  =  %10.3f\n", T) 
@printf("P (Pa) =  %10.3f\n", P) 
@printf("xH2O   =  %10.3f\n", xH2O) 
@printf("xCO2   =  %10.3f\n", xCO2) 
@printf("xCO    =  %10.3f\n", xCO) 
@printf("xCH4   =  %10.3f\n", xCH4) 

println("\n\nPlank Mean:")
println("   kabs (1/m),   awts")
@printf("%14.8f%14.8f", kabs_pm[1], awts_pm[1])

println("\n\nWSGG:")
println("   kabs (1/m),   awts")
for i in 1:length(kabs_wsgg)
    @printf("%14.8f%14.8f\n", kabs_wsgg[i], awts_wsgg[i])
end

println("\n\nRCSLW:")
println("   kabs (1/m),   awts")
for i in 1:length(kabs_rcslw)
    @printf("%14.8f%14.8f\n", kabs_rcslw[i], awts_rcslw[i])
end


