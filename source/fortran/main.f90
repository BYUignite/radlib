
program test

    use rad_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr

    type(C_ptr)                    :: r_pm
    type(C_ptr)                    :: r_wsgg
    type(C_ptr)                    :: r_rcslw
    double precision               :: T      = 2000.0;    ! K
    double precision               :: P      = 101325.0;  ! atm
    double precision               :: xH2O   = 0.8;       ! xH2O=0.2 is roughly stoich. CH4/air products
    double precision               :: xCO2   = 0.2;       ! xCO2=0.1 is roughly stoich. CH4/air products
    double precision               :: xCO    = 0.;
    double precision               :: xCH4   = 0.;
    double precision               :: fvsoot = 0.;
    double precision, dimension(1) :: kabs_pm
    double precision, dimension(1) :: awts_pm
    double precision, dimension(5) :: kabs_wsgg
    double precision, dimension(5) :: awts_wsgg
    double precision, dimension(5) :: kabs_rcslw
    double precision, dimension(5) :: awts_rcslw

    call rad_planck_mean(r_pm)
    call rad_wsgg(r_wsgg)
    call rad_rcslw(r_rcslw, size(kabs_rcslw)-1, P, T, xH2O, xCO2, xCO, fvsoot)

    call get_k_a(r_pm,    T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm)
    call get_k_a(r_wsgg , T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_wsgg,  awts_wsgg)
    call get_k_a(r_rcslw, T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_rcslw, awts_rcslw)

    write(*,*) kabs_pm(1), awts_pm(1)
    write(*,*)
    write(*,*) kabs_wsgg(1), awts_wsgg(1)
    write(*,*) kabs_wsgg(2), awts_wsgg(2)
    write(*,*) kabs_wsgg(3), awts_wsgg(3)
    write(*,*) kabs_wsgg(4), awts_wsgg(4)
    write(*,*) kabs_wsgg(5), awts_wsgg(5)
    write(*,*)
    write(*,*) kabs_rcslw(1), awts_rcslw(1)
    write(*,*) kabs_rcslw(2), awts_rcslw(2)
    write(*,*) kabs_rcslw(3), awts_rcslw(3)
    write(*,*) kabs_rcslw(4), awts_rcslw(4)
    write(*,*) kabs_rcslw(5), awts_rcslw(5)

end program test
