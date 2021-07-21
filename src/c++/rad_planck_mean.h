/**
 * @file rad_planck_mean.h
 * \brief Header file for child class rad_planck_mean
 */

#pragma once

#include <vector>
#include "rad.h"

////////////////////////////////////////////////////////////////////////////////

/** Class implementing rad_planck_mean object.
 *  Radiation properties for the Planck Mean model.
 *  A single "gas" is assumed.
 *  This is a simple, commonly used model in combustion, but is best for 
 *  situations that are optically thin with small radiative fractions.
 *  get_k_a, and get_k_a_oneband are the primary interfaces.
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

        void get_k_a(std::vector<double> &kabs,    // absorption coefficient (1/m)
                     std::vector<double> &awts,    // gas weight (sum to one)
                     const double   T,             // gas temperature (K)
                     const double   P,             // gas pressure (Pa)
                     const double   fvsoot,        // volume fraction soot (not ppmv)
                     const double   xH2O,          // mole fraction h2o
                     const double   xCO2,          // mole fraction co2
                     const double   xCO,           // mole fraction co
                     const double   xCH4);         // mole fraction ch4
        
        void get_k_a_oneband(double         &kabs,   // absorption coefficient (1/m)
                             double         &awts,   // gas weight (sum to one)
                             const int      iband,   // band/gas to get k_a for
                             const double   T,       // gas temperature (K)
                             const double   P,       // gas pressure (Pa)
                             const double   fvsoot,  // volume fraction soot (not ppmv)
                             const double   xH2O,    // mole fraction h2o
                             const double   xCO2,    // mole fraction co2
                             const double   xCO,     // mole fraction co
                             const double   xCH4);   // mole fraction ch4

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad_planck_mean()
            : rad(1, 1){}

};
