
program test

    use rad_module

    use, intrinsic :: ISO_C_Binding, only: C_ptr

    !==========================================================================

    !------------------ define parameters

    double precision               :: T      = 2000.0;    ! K
    double precision               :: P      = 101325.0;  ! atm
    double precision               :: xH2O   = 0.8;       ! xH2O=0.2 is roughly stoich. CH4/air products
    double precision               :: xCO2   = 0.2;       ! xCO2=0.1 is roughly stoich. CH4/air products
    double precision               :: xCO    = 0.;
    double precision               :: xCH4   = 0.;
    double precision               :: fvsoot = 0.;

    !------------------ declare variables and radiation objects

    double precision, dimension(1) :: kabs_pm
    double precision, dimension(1) :: awts_pm
    double precision, dimension(5) :: kabs_wsgg
    double precision, dimension(5) :: awts_wsgg
    double precision, dimension(5) :: kabs_rcslw
    double precision, dimension(5) :: awts_rcslw

    type(C_ptr)                    :: r_pm
    type(C_ptr)                    :: r_wsgg
    type(C_ptr)                    :: r_rcslw

    character(len=100) :: fmt1, fmt2

    !==========================================================================

    !------------------ create radiation objects

    call rad_planck_mean(r_pm)
    call rad_wsgg(r_wsgg)
    call rad_rcslw(r_rcslw, size(kabs_rcslw)-1, P, T, xH2O, xCO2, xCO, fvsoot)

    !------------------ compute absorption coefficients and weights

    call get_k_a(r_pm,    T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm)
    call get_k_a(r_wsgg , T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_wsgg,  awts_wsgg)
    call get_k_a(r_rcslw, T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_rcslw, awts_rcslw)

    !------------------ output results

    fmt1 = "(A9, F14.3)"
    fmt2 = "(2F14.8)"

    write(*,*)
    write(*,fmt1) "T (K)  = ", T
    write(*,fmt1) "P (Pa) = ", P
    write(*,fmt1) "xH2O   = ", xH2O
    write(*,fmt1) "xCO2   = ", xCO2
    write(*,fmt1) "xCO    = ", xCO 
    write(*,fmt1) "xCH4   = ", xCH4

    write(*,*)
    write(*,*) "Planck Mean:"
    write(*,*) "   kabs (1/m),   awts"
    write(*,fmt2) kabs_pm(1), awts_pm(1)

    write(*,*)
    write(*,*) "WSGG:"
    write(*,*) "   kabs (1/m),   awts"
    do i = 1, 5
        write(*,fmt2) kabs_wsgg(i), awts_wsgg(i)
    enddo

    write(*,*)
    write(*,*) "RCSLW:"
    write(*,*) "   kabs (1/m),   awts"
    do i = 1, 5
        write(*,fmt2) kabs_rcslw(i), awts_rcslw(i)
    enddo

end program test
