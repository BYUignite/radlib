include("/Users/dol4/codes/radlib/installed/include/radlib.jl")

using .radlib

r = rad_planck_mean()

println(r)
