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

        function rad_rcslw_C_interface(nGG, P, TbTref, xH2O, xCO2, xCO, fvsoot) &
                 result(rad_ptr) bind(C, name="rad_rcslw_C_interface")
            import
            type(C_ptr)    :: rad_ptr
            integer(C_int) :: nGG
            real(C_double) :: P
            real(C_double) :: TbTref
            real(C_double) :: xH2O
            real(C_double) :: xCO2
            real(C_double) :: xCO
            real(C_double) :: fvsoot
        end function rad_rcslw_C_interface

        !----------------------------------------------------------------------

        subroutine rad_delete_C_interface(rad_ptr) bind(C, name="rad_delete_C_interface")
            import
            type(C_ptr), value :: rad_ptr
        end subroutine rad_delete_C_interface

        !----------------------------------------------------------------------

        subroutine get_k_a_C_interface(rad_ptr, kabs, awts, T, P, xH2O, xCO2, xCO, xCH4, fvsoot) &
                bind(C, name="get_k_a_C_interface")
            import
            type(C_ptr), value           :: rad_ptr
            real(C_double), dimension(*) :: kabs
            real(C_double), dimension(*) :: awts
            real(C_double)               :: T
            real(C_double)               :: P
            real(C_double)               :: xH2O
            real(C_double)               :: xCO2
            real(C_double)               :: xCO
            real(C_double)               :: xCH4
            real(C_double)               :: fvsoot
        end subroutine get_k_a_C_interface

        !----------------------------------------------------------------------

    end interface

    !==========================================================================

    public :: rad_planck_mean, rad_wsgg, rad_rcslw, rad_delete, get_k_a

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

        subroutine rad_rcslw(rad_ptr, nGG, P, TbTref, xH2O, xCO2, xCO, fvsoot)
            type(C_ptr),      intent(out) :: rad_ptr
            integer,          intent(in)  :: nGG
            double precision, intent(in)  :: P
            double precision, intent(in)  :: TbTref
            double precision, intent(in)  :: xH2O
            double precision, intent(in)  :: xCO2
            double precision, intent(in)  :: xCO
            double precision, intent(in)  :: fvsoot
            rad_ptr = rad_rcslw_C_interface(nGG, P, TbTref, xH2O, xCO2, xCO, fvsoot)
        end subroutine rad_rcslw

        !----------------------------------------------------------------------

        subroutine rad_delete(rad_ptr)
            type(C_ptr), intent(inout) :: rad_ptr
            call rad_delete_C_interface(rad_ptr)
            rad_ptr = C_NULL_ptr
        end subroutine rad_delete

        !----------------------------------------------------------------------

        subroutine get_k_a(rad_ptr, kabs, awts, T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
            type(C_ptr),      intent(in)                :: rad_ptr
            double precision, intent(out), dimension(:) :: kabs
            double precision, intent(out), dimension(:) :: awts
            double precision, intent(in)                :: T
            double precision, intent(in)                :: P
            double precision, intent(in)                :: xH2O
            double precision, intent(in)                :: xCO2
            double precision, intent(in)                :: xCO
            double precision, intent(in)                :: xCH4
            double precision, intent(in)                :: fvsoot
            call get_k_a_C_interface(rad_ptr, kabs, awts, T, P, xH2O, xCO2, xCO, xCH4, fvsoot)
        end subroutine get_k_a

    !==========================================================================

end module rad_module
