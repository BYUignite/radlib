/**
 * @file rad_wsgg.h
 * Header file for class rad_wsgg
 */

#pragma once

#include "rad.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////////

/** Class implementing rad_wsgg object
 */

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

        //-------------- primary interface (note, P is set in constructor)

        void get_k_a(const double   T_dmb,         ///< gas temperature (K)
                     const double   P,             ///< gas pressure (Pa)
                     const double   xH2O,          ///< mole fraction H2O
                     const double   xCO2,          ///< mole fraction CO2
                     std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                     std::vector<double> &awts);   ///< gas weight (sum to one)

        //-------------- implementation of pure virtual abstract base class function
        //-------------- just calls the primary interface

        void get_k_a(const double   T_dmb,         ///< gas temperature (K)
                     const double   P,             ///< gas pressure (Pa); (interface only, set by constructor)
                     const double   xH2O,          ///< mole fraction H2O
                     const double   xCO2,          ///< mole fraction CO2
                     const double   xCO_not_used,  ///< mole fraction CO
                     const double   xCH4_not_used, ///< mole fraction CH4 (interface only, not used)
                     const double   fvsoot,        ///< volume fraction soot (not ppmv)
                     std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                     std::vector<double> &awts){   ///< gas weight (sum to one)
            get_k_a(T_dmb, P, xH2O, xCO2, kabs, awts);
        }
        
    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad_wsgg()
            : rad(4,5){}

        virtual ~rad_wsgg(){}

};
