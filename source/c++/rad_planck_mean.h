/**
 * @file rad_planck_mean.h
 * Header file for class rad_planck_mean
 */

#pragma once

#include <vector>
#include "rad.h"

////////////////////////////////////////////////////////////////////////////////

/** Class implementing rad_planck_mean object
 */

class rad_planck_mean : public rad {

    //////////////////// DATA MEMBERS //////////////////////

    protected:

        static const double pmCoefs_H2O[];
        static const double pmCoefs_CO2[];
        static const double pmCoefs_CO_lo[];   // < 750 K
        static const double pmCoefs_CO_hi[];   // > 750 K
        static const double pmCoefs_CH4[];

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        void get_k_a(const double   T,             ///< gas temperature (K)
                     const double   P,             ///< gas pressure (Pa)
                     const double   xH2O,          ///< mole fraction h2o
                     const double   xCO2,          ///< mole fraction co2
                     const double   xCO,           ///< mole fraction co
                     const double   xCH4,          ///< mole fraction ch4
                     const double   fvsoot,        ///< volume fraction soot (not ppmv)
                     std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                     std::vector<double> &awts);   ///< gas weight (sum to one)
        
    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad_planck_mean()
            : rad(1,1){}

};
