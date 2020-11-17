def ex_S5(method, nGG=24, use_Tmax=False):

    import numpy as np
    
    from cyparallel_planes import parallel_planes
    #from parallel_planes import parallel_planes
    
    from pyrad import pyrad_planck_mean as rad_planck_mean
    from pyrad import pyrad_wsgg        as rad_wsgg
    from pyrad import pyrad_rcslw       as rad_rcslw
    
    ################################################################################


    #--------------------- parameters
    
    P      = 101325.0
    L      = 2.0
    ntheta = 101
    nx     = 1001
    T0     = 1500.0
    TL     = 500.0
    
    nGGa   = nGG+1
    
    TT = 1500; xco2=0.0; xco=0.0; xh2o=0.1; fvs=0.0
    
    #---------------------
    
    xCO2   = np.full(nx, xco2, dtype=np.float64)
    xCO    = np.full(nx, xco,  dtype=np.float64)
    xH2O   = np.full(nx, xh2o, dtype=np.float64)
    xCH4   = np.full(nx, 0.0,  dtype=np.float64)
    fvsoot = np.full(nx, fvs,  dtype=np.float64)
    
    x = np.zeros(nx)
    T = np.full(nx,T0, dtype=np.float64)
    
    dx = L/(nx-1)
    x[0] = 0.0
    Tavg = T[0]
    for i in range(1,nx):
        x[i] = x[i-1] + dx
        T[i] = 1000.0 + 500*np.cos(np.pi*x[i]/L)
        Tavg += T[i]
    Tavg /= nx
    
    if method=='rcslw':
        rad = rad_rcslw(nGG, P, TT if use_Tmax else Tavg, xh2o, xco2, xco, fvs)     # TT gives better results than Tavg
    elif method=='wsgg':
        rad = rad_wsgg()
    elif method=='planckmean':
        rad = rad_planck_mean()
    else:
        raise ValueError('unknown radiation method')
    
    #------------------- get q, Q
    
    x, xQ, q, Q = parallel_planes(rad, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot)
    
    print("# x (m), Q (kW/m3)")
    for i in range(len(xQ)):
        print(f'{xQ[i]:.5f}  {Q[i]/1000:.5f}')
    
    #print("# x (m), q (kW/m2)")
    #for i in range(len(x)):
    #    print(f'{x[i]:.5f}  {q[i]/1000:.5f}')
    
        #-------------------------------------------------------------------------
    
    print()
    return xQ, Q

################################################################################

if __name__=='__main__':
    xQ, Q = ex_S5('rcslw', 25, True)
