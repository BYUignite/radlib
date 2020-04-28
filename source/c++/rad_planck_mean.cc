/**
 * @file rad_planck_mean.cc
 * Source file for class rad_planck_mean
 */

#include "rad_planck_mean.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////

const double rad_planck_mean::pmCoefs_H2O[6]   = {-0.23093, -1.12390,   9.41530,    -2.99880,     0.51382,     -1.86840E-5};
const double rad_planck_mean::pmCoefs_CO2[6]   = {18.741,   -121.310,   273.500,    -194.050,     56.310,      -5.8169};
const double rad_planck_mean::pmCoefs_CO_lo[5] = {4.7869,   -0.06953,   2.95775E-4, -4.25732E-7,  2.02894E-10};
const double rad_planck_mean::pmCoefs_CO_hi[5] = {10.09,    -0.01183,   4.7753E-6,  -5.87209E-10, -2.5334E-14};
const double rad_planck_mean::pmCoefs_CH4[5]   = {6.6334,   -0.0035686, 1.6682E-08, 2.5611E-10,   -2.6558E-14};

///////////////////////////////////////////////////////////////////////////////
/** THIS IS THE CLASS INTERFACE FUNCTION
 *  Given the gas state, set the k and a vectors.
 *  These can then be accessed by the user.
 *  return through arg list the local gray gas coefficients (kabs) and the local weights (awts).
 *  @param T               \input gas temperature
 *  @param P_not_used      \input Pressure (Pa)
 *  @param xH2O            \input mole fraction H2O
 *  @param xCO2            \input mole fraction CO2
 *  @param xCO             \input mole fraction CO
 *  @param xCH4_not_used   \input mole fraction CH4
 *  @param fvsoot          \input soot volume fraction = rho*Ysoot/rhosoot
 *  @param kabs            \output absorption coefficients (1/m); size = 1 here (1 gas)
 *  @param awts            \output weights (unitless; sums to 1); size = 1 here (1 gas)
 */

void rad_planck_mean::get_k_a(const double   T,
                              const double   P,
                              const double   xH2O,
                              const double   xCO2,
                              const double   xCO,
                              const double   xCH4,
                              const double   fvsoot,
                              vector<double> &kabs,
                              vector<double> &awts){

    awts.resize(1);  awts[0] = 1.0; 
    kabs.resize(1);  kabs[0] = 0.0;

    double K;
    double Ti = 1000.0/T;

    //------------- H2O

    if(xH2O != 0.0){
        K = pmCoefs_H2O[0] + Ti*(pmCoefs_H2O[1] + Ti*(pmCoefs_H2O[2] + Ti*(pmCoefs_H2O[3] + Ti*(pmCoefs_H2O[4] + Ti*(pmCoefs_H2O[5])))));
        kabs[0] += xH2O*P/101325.0*K;
    }

    //------------- CO2

    if(xCO2 != 0.0){
        K = pmCoefs_CO2[0] + Ti*(pmCoefs_CO2[1] + Ti*(pmCoefs_CO2[2] + Ti*(pmCoefs_CO2[3] + Ti*(pmCoefs_CO2[4] + Ti*(pmCoefs_CO2[5])))));
        kabs[0] += xCO2*P/101325.0*K;
    }

    //------------- CO

    if(xCO != 0.0) {
        if(T <= 750.0)
            K = pmCoefs_CO_lo[0] + T*(pmCoefs_CO_lo[1] + T*(pmCoefs_CO_lo[2] + T*(pmCoefs_CO_lo[3] + T*(pmCoefs_CO_lo[4]))));
        else
            K = pmCoefs_CO_hi[0] + T*(pmCoefs_CO_hi[1] + T*(pmCoefs_CO_hi[2] + T*(pmCoefs_CO_hi[3] + T*(pmCoefs_CO_hi[4]))));
        kabs[0] += xCO*P/101325.0*K;
    }

    //------------- CH4

    if(xCH4 != 0.0){
        K = pmCoefs_CH4[0] + T*(pmCoefs_CH4[1] + T*(pmCoefs_CH4[2] + T*(pmCoefs_CH4[3] + T*(pmCoefs_CH4[4]))));
        kabs[0] += xCH4*P/101325.0*K;
    }

    //------------- soot

    //if(fvsoot != 0.0){
    //}


}
