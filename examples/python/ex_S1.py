def ex_S1(method, nGG=24):
    
    import numpy as np
    import time
    
    from cyparallel_planes import parallel_planes
    #from parallel_planes import parallel_planes
    
    from pyrad import pyrad_planck_mean as rad_planck_mean
    from pyrad import pyrad_wsgg        as rad_wsgg
    from pyrad import pyrad_rcslw       as rad_rcslw
    
    sigma = 5.670367E-8     # Stephan-Boltzmann constant
    
    ################################################################################
    
    #--------------------- parameters
    
    t0 = time.time()
    
    P      = 101325.0
    Thot   = 2000
    Tcold  = 300
    Lhot   = 0.5
    ntheta = 101
    nxh    = 1001    # for Lcold=0 changes below to keep dx roughly constant
    
    Lcold  = np.array([0, 0.01, 0.025, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.75, 1.0, 1.5, 2.0])
    
    nGGa   = nGG+1
    
    xco2=0.1; xco=0.0; xh2o=0.2; xch4=0.0; fvs=0.0
    
    #---------------------
    
    print("# Lcold (m),     q(L)/σThot^4")
    
    qsigT4 = np.empty(len(Lcold))
    
    for iLcold in range(len(Lcold)):
    
        L  = Lcold[iLcold] + Lhot
    
        Tavg = (Thot*0.5+Tcold*Lcold[iLcold])/L
    
        nx = int(nxh*L/Lhot)
    
        xCO2   = np.full(nx, xco2, dtype=np.float64)
        xCO    = np.full(nx, xco,  dtype=np.float64)
        xH2O   = np.full(nx, xh2o, dtype=np.float64)
        xCH4   = np.full(nx, xch4, dtype=np.float64)
        fvsoot = np.full(nx, fvs,  dtype=np.float64)
    
        x = np.zeros(nx)
        dx = L/(nx-1)
        T = np.full(nx, Thot, dtype=np.float64)
        for i in range(1,nx):        # mimic c++; pythonic gives different grid/T due to roundoff
            x[i] = x[i-1] + dx
            T[i] = Thot if x[i] <= Lhot else Tcold
    
        if method=='rcslw':
            rad = rad_rcslw(nGG, P, Tavg, xh2o, xco2, xco, fvs)
        elif method=='wsgg':
            rad = rad_wsgg()
        elif method=='planckmean':
            rad = rad_planck_mean()
        else:
            raise ValueError('unknown radiation method')
    
        #--------------------- get q, Q
    
        x, xQ, q, Q = parallel_planes(rad, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, True)
    
        #-------------------------------------------------------------------------
    
        qsigT4[iLcold] = q[nx-1]/sigma/Thot**4
    
        print(f'{Lcold[iLcold]:10.3f}  {qsigT4[iLcold]:15.5f}')
    
    print(f'runtime = {time.time()-t0}')
    print()

    return Lcold, qsigT4

################################################################################
    
if __name__=='__main__':
    Lcold, qsigT4 = ex_S1('rcslw', 24)
