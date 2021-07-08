#include "../c++/rad_planck_mean.h"
#include "../c++/rad_wsgg.h"
#include "../c++/rad_rcslw.h"
#include <vector>
#include <iostream>

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
                               double *TbTref,
                               double *P,
                               double *fvsoot,
                               double *xH2O,
                               double *xCO2,
                               double *xCO){

        return new rad_rcslw(*nGG, *TbTref, *P, *fvsoot, *xH2O, *xCO2, *xCO);
    }
    //-------------------------------------------------------------------------

    void rad_delete_C_interface(rad *rad_ptr){
        delete rad_ptr;
    }
    //-------------------------------------------------------------------------

    void get_k_a_C_interface(rad    *rad_ptr,
                             double *kabs,
                             double *awts,
                             double *T,
                             double *P,
                             double *fvsoot,    
                             double *xH2O,
                             double *xCO2,
                             double *xCO,
                             double *xCH4){

        vector<double> kk(rad_ptr->get_nGGa());
        vector<double> aa(rad_ptr->get_nGGa());

        rad_ptr->get_k_a(kk, aa, *T, *P, *fvsoot, *xH2O, *xCO2, *xCO, *xCH4);

        for(int i=0; i<kk.size(); ++i){
            kabs[i] = kk[i];
            awts[i] = aa[i];
        }

    }
    //-------------------------------------------------------------------------

    void get_k_a_1band_C_interface(rad    *rad_ptr,
                                   double *kabs,
                                   double *awts,
                                   int    *iband,
                                   double *T,
                                   double *P,
                                   double *fvsoot,    
                                   double *xH2O,
                                   double *xCO2,
                                   double *xCO,
                                   double *xCH4){

        rad_ptr->get_k_a_1band(*kabs, *awts, *iband, *T, *P, *fvsoot, *xH2O, *xCO2, *xCO, *xCH4);
    }
}
