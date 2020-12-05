def ex_Sb1(method, fvs, nGG=24):

    import numpy as np
    
    from cyparallel_planes import parallel_planes
    #from parallel_planes import parallel_planes
    
    from pyrad import pyrad_planck_mean as rad_planck_mean
    from pyrad import pyrad_wsgg        as rad_wsgg
    from pyrad import pyrad_rcslw       as rad_rcslw
    
    ################################################################################
    
    #--------------------- parameters
    
    P      = 101325.0
    L      = 1.0
    ntheta = 101
    nx     = 1001
    Tconst = 1000.0
    
    nGGa   = nGG+1
    
    xco2=0.1; xco=0.03; xh2o=0.2; xch4=0.0
    
    #---------------------
    
    xCO2   = np.full(nx, xco2, dtype=np.float64)
    xCO    = np.full(nx, xco,  dtype=np.float64)
    xH2O   = np.full(nx, xh2o, dtype=np.float64)
    xCH4   = np.full(nx, xch4, dtype=np.float64)
    fvsoot = np.full(nx, fvs,  dtype=np.float64)
    
    x = np.zeros(nx)
    T = np.full(nx,Tconst, dtype=np.float64)
    
    dx = L/(nx-1)
    x[0] = 0.0
    for i in range(1,nx):
        x[i] = x[i-1] + dx
    
    if method=='rcslw':
        rad = rad_rcslw(nGG, P, Tconst, xh2o, xco2, xco, fvs)
    elif method=='wsgg':
        rad = rad_wsgg()
    elif method=='planckmean':
        rad = rad_planck_mean()
    else:
        raise ValueError('unknown radiation method')
    
    #------------------- get q, Q
    
    x, xQ, q, Q = parallel_planes(rad, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, True)
    
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
    xQ, Q = ex_S3('rcslw', 24)
