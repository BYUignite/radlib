#include "../c++/rad_planck_mean.h"
#include "../c++/rad_wsgg.h"
#include "../c++/rad_rcslw.h"
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////

extern "C"{

    //-------------------------------------------------------------------------

    rad *rad_planck_mean_C_interface(){
        return new rad_planck_mean();
    }
    //-------------------------------------------------------------------------

    rad *rad_wsgg_C_interface(){
        return new rad_wsgg();
    }
    //-------------------------------------------------------------------------

    rad *rad_rcslw_C_interface(int    *nGG,
                               double *P,
                               double *TbTref,
                               double *xH2O,
                               double *xCO2,
                               double *xCO,
                               double *fvsoot){

        return new rad_rcslw(*nGG, *P, *TbTref, *xH2O, *xCO2, *xCO, *fvsoot);
    }
    //-------------------------------------------------------------------------

    void rad_delete_C_interface(rad *rad_ptr){
        delete rad_ptr;
    }
    //-------------------------------------------------------------------------

    void get_k_a_C_interface(rad *rad_ptr,
                             double *T,
                             double *P,
                             double *xH2O,
                             double *xCO2,
                             double *xCO,
                             double *xCH4,
                             double *fvsoot,
                             double *kabs,
                             double *awts){

        vector<double> kk(rad_ptr->get_nGGa());
        vector<double> aa(rad_ptr->get_nGGa());
        for(int i=0; i<kk.size(); ++i){
            kk[i] = kabs[i];
            aa[i] = awts[i];
        }

        rad_ptr->get_k_a(*T, *P, *xH2O, *xCO2, *xCO, *xCH4, *fvsoot, kk, aa);

        for(int i=0; i<kk.size(); ++i){
            kabs[i] = kk[i];
            awts[i] = aa[i];
        }

    }
    //-------------------------------------------------------------------------
}
