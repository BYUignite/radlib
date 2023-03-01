#include <vector>
#include "jlcxx/jlcxx.hpp"
#include "rad.h"
#include "rad_planck_mean.h"
#include "rad_wsgg.h"
#include "rad_rcslw.h"

///////////////////////////////////////////////////////////////////////////////

namespace jlcxx {

template<> class SuperType<rad_planck_mean> { public: typedef rad type; };
template<> class SuperType<rad_wsgg>        { public: typedef rad type; };
template<> class SuperType<rad_rcslw>       { public: typedef rad type; };

}

///////////////////////////////////////////////////////////////////////////////

JLCXX_MODULE define_radlib_module(jlcxx::Module &mod) {

    mod.add_type<rad>("rad")
        .method("get_k_a",         &rad::get_k_a)
        .method("get_k_a_oneband", &rad::get_k_a_oneband)
        .method("get_nGG",         &rad::get_nGG)
        .method("get_nGGa",        &rad::get_nGGa);

    mod.add_type<rad_planck_mean>("rad_planck_mean", jlcxx::julia_base_type<rad>())

    mod.add_type<rad_wsgg>("rad_wsgg", jlcxx::julia_base_type<rad>());

    mod.add_type<rad_rcslw>("rad_rcslw", jlcxx::julia_base_type<rad>())
        .constructor<int, double, double, double, double, double, double>();
}

