def ex_S2(method, nGG=24):

    import numpy as np
    
    from cyparallel_planes import parallel_planes
    #from parallel_planes import parallel_planes
    
    from pyrad import pyrad_planck_mean as rad_planck_mean
    from pyrad import pyrad_wsgg        as rad_wsgg
    from pyrad import pyrad_rcslw       as rad_rcslw
    
    sigma = 5.670367E-8     # Stephan-Boltzmann constant
    
    ################################################################################
    
    #--------------------- parameters
    
    TT     = 1000.0
    P      = 101325.0
    xco2_1 = 0.4
    xco2_2 = 0.1
    Lhot   = 0.5
    ntheta = 101
    nxh    = 1001    # for Lcold=0 changes below to keep dx roughly constant
    
    Lcold  = np.array([0, 0.01, 0.025, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.75, 1.0, 1.5, 2.0])
    
    nGGa   = nGG+1
    
    xco = 0.0; xh2o=0.0; xch4=0.0; fvs = 0.0
    
    #---------------------
    
    print("# Lcold (m),     q(L)/σT^4")
    
    qsigT4 = np.empty(len(Lcold))
    
    for iLcold in range(len(Lcold)):
    
        L  = Lcold[iLcold] + Lhot
    
        xco2_avg = (xco2_1*0.5+xco2_2*Lcold[iLcold])/L
    
        nx = int(nxh*L/Lhot)
    
        xCO2   = np.full(nx, xco2_1, dtype=np.float64)
        xCO    = np.full(nx, xco,    dtype=np.float64)
        xH2O   = np.full(nx, xh2o,   dtype=np.float64)
        xCH4   = np.full(nx, xch4,   dtype=np.float64)
        fvsoot = np.full(nx, fvs,    dtype=np.float64)
    
        x = np.zeros(nx)
        dx = L/(nx-1)
        T = np.full(nx, TT, dtype=np.float64)
        for i in range(1,nx):        # mimic c++; pythonic gives different grid/T due to roundoff
            x[i] = x[i-1] + dx
            xCO2[i] = xco2_1 if x[i] <= Lhot else xco2_2
    
        if method=='rcslw':
            rad = rad_rcslw(nGG, P, TT, xh2o, xco2_avg, xco, fvs)
        elif method=='wsgg':
            rad = rad_wsgg()
        elif method=='planckmean':
            rad = rad_planck_mean()
        else:
            raise ValueError('unknown radiation method')
    
        #--------------------- get q, Q
    
        x, xQ, q, Q = parallel_planes(rad, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, True)
    
        #-------------------------------------------------------------------------
    
        qsigT4[iLcold] = q[nx-1]/sigma/TT**4
    
        print(f'{Lcold[iLcold]:10.3f}  {qsigT4[iLcold]:15.5f}')

    print()
    return Lcold, qsigT4

################################################################################
    
if __name__=='__main__':
    Lcold, qsigT4 = ex_S2('rcslw', 24)
