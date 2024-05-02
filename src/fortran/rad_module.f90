module rad_module

    use, intrinsic :: ISO_C_Binding, only: C_int, C_double, C_ptr, C_NULL_ptr

    implicit none

    private

    !==========================================================================
    ! declare the C interface

    interface

        !----------------------------------------------------------------------

        function rad_planck_mean_C_interface() result(rad_ptr) bind(C, name="rad_planck_mean_C_interface")
            import
            type(C_ptr) :: rad_ptr
        end function rad_planck_mean_C_interface

        !----------------------------------------------------------------------

        function rad_wsgg_C_interface() result(rad_ptr) bind(C, name="rad_wsgg_C_interface")
            import
            type(C_ptr) :: rad_ptr
        end function rad_wsgg_C_interface

        !----------------------------------------------------------------------

        function rad_rcslw_C_interface(nGG, TbTref, P, fvsoot, xH2O, xCO2, xCO) &
                 result(rad_ptr) bind(C, name="rad_rcslw_C_interface")
            import
            type(C_ptr)    :: rad_ptr
            integer(C_int) :: nGG
            real(C_double) :: TbTref
            real(C_double) :: P
            real(C_double) :: fvsoot
            real(C_double) :: xH2O
            real(C_double) :: xCO2
            real(C_double) :: xCO
        end function rad_rcslw_C_interface

        !----------------------------------------------------------------------

        subroutine rad_delete_C_interface(rad_ptr) bind(C, name="rad_delete_C_interface")
            import
            type(C_ptr), value :: rad_ptr
        end subroutine rad_delete_C_interface

        !----------------------------------------------------------------------

        subroutine get_k_a_C_interface(rad_ptr, kabs, awts, T, P, fvsoot, xH2O, xCO2, xCO, xCH4) &
                bind(C, name="get_k_a_C_interface")
            import
            type(C_ptr), value           :: rad_ptr
            real(C_double), dimension(*) :: kabs
            real(C_double), dimension(*) :: awts
            real(C_double)               :: T
            real(C_double)               :: P
            real(C_double)               :: fvsoot
            real(C_double)               :: xH2O
            real(C_double)               :: xCO2
            real(C_double)               :: xCO
            real(C_double)               :: xCH4
        end subroutine get_k_a_C_interface

        !----------------------------------------------------------------------

        subroutine get_k_a_oneband_C_interface(rad_ptr, kabs, awts, iband, T, P, fvsoot, xH2O, xCO2, xCO, xCH4) &
                bind(C, name="get_k_a_oneband_C_interface")
            import
            type(C_ptr), value           :: rad_ptr
            real(C_double)               :: kabs
            real(C_double)               :: awts
            integer(C_int)               :: iband
            real(C_double)               :: T
            real(C_double)               :: P
            real(C_double)               :: fvsoot
            real(C_double)               :: xH2O
            real(C_double)               :: xCO2
            real(C_double)               :: xCO
            real(C_double)               :: xCH4
        end subroutine get_k_a_oneband_C_interface

        !----------------------------------------------------------------------

    end interface

    !==========================================================================

    public :: rad_planck_mean, rad_wsgg, rad_rcslw, rad_delete, get_k_a, get_k_a_oneband

    !==========================================================================
    ! set fortran wrapper routines to the C interface functions

    contains

        !----------------------------------------------------------------------

        subroutine rad_planck_mean(rad_ptr)
            type(C_ptr), intent(out) :: rad_ptr
            rad_ptr = rad_planck_mean_C_interface()
        end subroutine rad_planck_mean

        !----------------------------------------------------------------------

        subroutine rad_wsgg(rad_ptr)
            type(C_ptr), intent(out) :: rad_ptr
            rad_ptr = rad_wsgg_C_interface()
        end subroutine rad_wsgg

        !----------------------------------------------------------------------

        subroutine rad_rcslw(rad_ptr, nGG, TbTref, P, fvsoot, xH2O, xCO2, xCO)
            type(C_ptr),      intent(out) :: rad_ptr
            integer,          intent(in)  :: nGG
            double precision, intent(in)  :: TbTref
            double precision, intent(in)  :: P
            double precision, intent(in)  :: fvsoot
            double precision, intent(in)  :: xH2O
            double precision, intent(in)  :: xCO2
            double precision, intent(in)  :: xCO
            rad_ptr = rad_rcslw_C_interface(nGG, TbTref, P, fvsoot, xH2O, xCO2, xCO)
        end subroutine rad_rcslw

        !----------------------------------------------------------------------

        subroutine rad_delete(rad_ptr)
            type(C_ptr), intent(inout) :: rad_ptr
            call rad_delete_C_interface(rad_ptr)
            rad_ptr = C_NULL_ptr
        end subroutine rad_delete

        !----------------------------------------------------------------------

        subroutine get_k_a(rad_ptr, kabs, awts, T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
            type(C_ptr),      intent(in)                :: rad_ptr
            double precision, intent(out), dimension(:) :: kabs
            double precision, intent(out), dimension(:) :: awts
            double precision, intent(in)                :: T
            double precision, intent(in)                :: P
            double precision, intent(in)                :: fvsoot
            double precision, intent(in)                :: xH2O
            double precision, intent(in)                :: xCO2
            double precision, intent(in), optional      :: xCO
            double precision, intent(in), optional      :: xCH4
            
            double precision :: xxCO
            double precision :: xxCH4

            if (present(xCO)) then
                xxCO = xCO
            end if
            if (present(xCH4)) then
                xxCH4 = xCH4
            end if

            call get_k_a_C_interface(rad_ptr, kabs, awts, T, P, fvsoot, xH2O, xCO2, xxCO, xxCH4)
        end subroutine get_k_a

        !----------------------------------------------------------------------

        subroutine get_k_a_oneband(rad_ptr, kabs, awts, iband, T, P, fvsoot, xH2O, xCO2, xCO, xCH4)
            type(C_ptr),      intent(in)                :: rad_ptr
            double precision, intent(out)               :: kabs
            double precision, intent(out)               :: awts
            integer,          intent(in)                :: iband
            double precision, intent(in)                :: T
            double precision, intent(in)                :: P
            double precision, intent(in)                :: fvsoot
            double precision, intent(in)                :: xH2O
            double precision, intent(in)                :: xCO2
            double precision, intent(in), optional      :: xCO
            double precision, intent(in), optional      :: xCH4

            double precision :: xxCO
            double precision :: xxCH4

            if (present(xCO)) then
                xxCO = xCO
            end if
            if (present(xCH4)) then
                xxCH4 = xCH4
            end if

            call get_k_a_oneband_C_interface(rad_ptr, kabs, awts, iband, T, P, fvsoot, xH2O, xCO2, xxCO, xxCH4)
        end subroutine get_k_a_oneband

    !==========================================================================

end module rad_module
