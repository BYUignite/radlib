def ex_B3(method, nGG=4):

    import numpy as np
    
    from cyparallel_planes import parallel_planes
    #from parallel_planes import parallel_planes
    
    from pyrad import pyrad_planck_mean as rad_planck_mean
    from pyrad import pyrad_wsgg        as rad_wsgg
    from pyrad import pyrad_rcslw       as rad_rcslw
    
    ################################################################################
    
    #--------------------- parameters

    nGGa = nGG + 1
    
    P      = 101325.0
    L      = 1.0
    ntheta = 101
    nx     = 1001
    Twall  = 400.0
    
    xco2=0.0; xco=0.0; xh2o=0.0; xch4=0.0; fvs=0.0
    
    #---------------------
    
    xCO2   = np.full(nx, xco2, dtype=np.float64)
    xCO    = np.full(nx, xco,  dtype=np.float64)
    xH2O   = np.full(nx, xh2o, dtype=np.float64)
    xCH4   = np.full(nx, xch4, dtype=np.float64)
    fvsoot = np.full(nx, fvs,  dtype=np.float64)
    
    x = np.zeros(nx)
    T = np.full(nx,Twall, dtype=np.float64)
    
    x = np.linspace(0,L,nx)
    for i in range(nx):
        T[i]    = 400.0 + 1400.0*   np.sin(np.pi*x[i]/L)**2
        xH2O[i] = 1E-4 + (1.0-1E-4)*np.sin(np.pi*x[i]/L)**2
        xCO2[i] = 1.0-xH2O[i]
    xH2O_avg = np.average(xH2O)
    xCO2_avg = 1.0-xH2O_avg
    T_avg    = np.average(T)
    
    if method=='rcslw':
        rad = rad_rcslw(nGG, P, T_avg, xH2O_avg, xCO2_avg, xco, fvs)
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

    return x, xQ, q, Q

################################################################################
    
if __name__=='__main__':
    x, xQ, q, Q = ex_B3('wsgg', nGG=4)
