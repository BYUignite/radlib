module radlib
    using CxxWrap

    @wrapmodule("libradlib_julia", :define_radlib_module)

    function __init__()
        @initcxx
    end

    export rad_planck_mean
end


