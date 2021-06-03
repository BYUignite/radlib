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
            type(C_ptr), value :: rad_ptr
        end function rad_planck_mean_C_interface

        !----------------------------------------------------------------------

        subroutine rad_planck_mean_delete_C_interface(rad_ptr) bind(C, name="rad_planck_mean_delete_C_interface")
            import
            type(C_ptr), value :: rad_ptr
        end subroutine rad_planck_mean_delete_C_interface

        !----------------------------------------------------------------------

        subroutine get_k_a_C_interface(rad_ptr, T, P, xH2O, xCO2, xCO, fvsoot, kabs, awts) &
                bind(C, name="get_k_a_C_interface")
            import
            type(C_ptr), value           :: rad_ptr
            real(C_double)               :: T
            real(C_double)               :: P
            real(C_double)               :: xH2O
            real(C_double)               :: xCO2
            real(C_double)               :: xCO
            real(C_double)               :: fvsoot
            real(C_double), dimension(1) :: kabs
            real(C_double), dimension(1) :: awts
        end subroutine get_k_a_C_interface

        !----------------------------------------------------------------------

    end interface

    !==========================================================================

    public :: rad_planck_mean, rad_planck_mean_delete, get_k_a

    !==========================================================================
    ! set fortran wrapper routines to the C interface functions

    contains

        !----------------------------------------------------------------------

        subroutine rad_planck_mean(rad_ptr)
            type(C_ptr), intent(out) :: rad_ptr
            rad_ptr = rad_planck_mean_C_interface()
        end subroutine rad_planck_mean

        !----------------------------------------------------------------------

        subroutine rad_planck_mean_delete(rad_ptr)
            type(C_ptr), intent(inout) :: rad_ptr
            call rad_planck_mean_delete_C_interface(rad_ptr)
            rad_ptr = C_NULL_ptr
        end subroutine rad_planck_mean_delete

        !----------------------------------------------------------------------

        subroutine get_k_a(rad_ptr, T, P, xH2O, xCO2, xCO, fvsoot, kabs, awts)
            type(C_ptr), intent(in)                   :: rad_ptr
            real(C_double), intent(in)                :: T
            real(C_double), intent(in)                :: P
            real(C_double), intent(in)                :: xH2O
            real(C_double), intent(in)                :: xCO2
            real(C_double), intent(in)                :: xCO
            real(C_double), intent(in)                :: fvsoot
            real(C_double), intent(out), dimension(1) :: kabs
            real(C_double), intent(out), dimension(1) :: awts
            call get_k_a_C_interface(rad_ptr, T, P, xH2O, xCO2, xCO, fvsoot, kabs, awts)
        end subroutine get_k_a

    !==========================================================================

end module rad_module
