/// @file rad_wsgg.h
/// \brief Header file for child class rad_wsgg

#pragma once

#include "rad.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////
///
/// Class implementing rad_wsgg object.
/// Radiation properties for the WSGG model (Bordbar 2020).
/// Four gray gases and one clear gas are assumed.
/// This is somewhat less accurate than the RCSLW model, but less computationally expensive.
/// get_k_a, and get_k_a_oneband are the primary interfaces.
///
////////////////////////////////////////////////////////////////////////////////

class rad_wsgg : public rad {

    //////////////////// DATA MEMBERS //////////////////////

    protected:

        static const double cCoefs[];        ///< map to [i,j,k] of size ni,nj,nk = 4,5,5
        static const double dCoefs[];        ///> map to [i,k]   of size ni,nk    = 4,5
        static const double bco2[];          ///> map to [i,j]   of size ni,nj    = 4,5
        static const double bh2o[];          ///> map to [i,j]   of size ni,nj    = 4,5
        static const double kco2[];          ///> absorption coefficients for pure co2 (size 5 = nGGa)
        static const double kh2o[];          ///> absorption coefficients for pure h2o (size 5 = nGGa)

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        void get_k_a(std::vector<double> &kabs,     // absorption coefficient (1/m)
                     std::vector<double> &awts,     // gas weight (sum to one)
                     const double   T_dmb,          // gas temperature (K)
                     const double   P,              // gas pressure (Pa)
                     const double   fvsoot,         // volume fraction soot (not ppmv)
                     const double   xH2O,           // mole fraction H2O
                     const double   xCO2,           // mole fraction CO2
                     const double   xCO_not_used,   // mole fraction CO (interface only, not used)
                     const double   xCH4_not_used); // mole fraction CH4 (interface only, not used)

        void get_k_a_oneband(double         &kabs,            // absorption coefficient (1/m)
                             double         &awts,            // gas weight (sum to one)
                             const int      iband,            // band/gas to get k_a for
                             const double   T,                // gas temperature (K)
                             const double   P,                // gas pressure (Pa)
                             const double   fvsoot,           // volume fraction soot (not ppmv)
                             const double   xH2O,             // mole fraction h2o
                             const double   xCO2,             // mole fraction co2
                             const double   xCO_not_used,     // mole fraction co
                             const double   xCH4_not_used);   // mole fraction ch4
        
    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad_wsgg()
            : rad(4, 5){}

        virtual ~rad_wsgg(){}

};
