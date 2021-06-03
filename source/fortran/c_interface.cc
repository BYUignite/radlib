#include "rad_planck_mean.h"

//////////////////////////////////////////////////////////////////////////////////////////

extern "C"{

    //-------------------------------------------------------------------------

    rad *rad_planck_mean_C_interface(){
        return new rad_planck_mean();
    }
    //-------------------------------------------------------------------------

    void rad_planck_mean_delete_C_interface(rad *rad_ptr){
        delete rad_ptr;    
    }
    //-------------------------------------------------------------------------

    void get_k_a_C_interface(rad *rad_ptr,
                             double *T,
                             double *P,
                             double *xH2O,
                             double *xCO2,
                             double *xCO,
                             double *fvsoot,
                             double *kabs,
                             double *awts){

        vector<double> kk(1, kabs[0]);
        vector<double> aa(1, awts[0]);

        rad_ptr->get_k_a(*T, *P, *xH2O, *xCO2, *xCO, *xCH4, *fvsoot, kk, aa);

        kabs[0] = kk[0]; 
        awts[0] = aa[0]; 
    }
    //-------------------------------------------------------------------------
}
