module radlib
    using CxxWrap

    @wrapmodule("/Users/dol4/codes/radlib/installed/lib/libradlib_julia", :define_radlib_module)

    function __init__()
        @initcxx
    end

    export rad_planck_mean, rad_wsgg, rad_rcslw        # constructors
    export get_nGG, get_nGGa
    export get_k_a
end


