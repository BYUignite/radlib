/**
 * @file rad_wsgg.cc
 * \brief Source file for child class rad_wsgg
 */

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "rad_wsgg.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////

const double rad_wsgg::cCoefs[100]={7.412956e-001, -5.244441e-001,  5.822860e-001, -2.096994e-001,  2.420312e-002,
                                   -9.412652e-001,  2.799577e-001, -7.672319e-001,  3.204027e-001, -3.910174e-002,
                                    8.531866e-001,  8.230754e-002,  5.289430e-001, -2.468463e-001,  3.109396e-002,
                                   -3.342806e-001,  1.474987e-001, -4.160689e-001,  1.697627e-001, -2.040660e-002,
                                    4.314362e-002, -6.886217e-002,  1.109773e-001, -4.208608e-002,  4.918817e-003,
                                    1.552073e-001, -4.862117e-001,  3.668088e-001, -1.055508e-001,  1.058568e-002,
                                    6.755648e-001,  1.409271e+000, -1.383449e+000,  4.575210e-001, -5.019760e-002,
                                   -1.125394e+000, -5.913199e-001,  9.085441e-001, -3.334201e-001,  3.842361e-002,
                                    6.040543e-001, -5.533854e-002, -1.733014e-001,  7.916083e-002, -9.893357e-003,
                                   -1.105453e-001,  4.646634e-002, -1.612982e-003, -3.539835e-003,  6.121277e-004,
                                    2.550242e-001,  3.805403e-001, -4.249709e-001,  1.429446e-001, -1.574075e-002,
                                   -6.065428e-001,  3.494024e-001,  1.853509e-001, -1.013694e-001,  1.302441e-002,
                                    8.123855e-001, -1.102009e+000,  4.046178e-001, -8.118223e-002,  6.298101e-003,
                                   -4.532290e-001,  6.784475e-001, -3.432603e-001,  8.830883e-002, -8.415221e-003,
                                    8.693093e-002, -1.306996e-001,  7.414464e-002, -2.029294e-002,  2.010969e-003,
                                   -3.451994e-002,  2.656726e-001, -1.225365e-001,  3.001508e-002, -2.820525e-003,
                                    4.112046e-001, -5.728350e-001,  2.924490e-001, -7.980766e-002,  7.996603e-003,
                                   -5.055995e-001,  4.579559e-001, -2.616436e-001,  7.648413e-002, -7.908356e-003,
                                    2.317509e-001, -1.656759e-001,  1.052608e-001, -3.219347e-002,  3.386965e-003,
                                   -3.754908e-002,  2.295193e-002, -1.600472e-002,  5.046318e-003, -5.364326e-004};

const double rad_wsgg::dCoefs[20]={3.404288e-002,  6.523048e-002, -4.636852e-002,  1.386835e-002, -1.444993e-003,
                                   3.509457e-001,  7.465138e-001, -5.293090e-001,  1.594423e-001, -1.663261e-002,
                                   4.570740e+000,  2.168067e+000, -1.498901e+000,  4.917165e-001, -5.429990e-002,
                                   1.098169e+002, -5.092359e+001,  2.343236e+001, -5.163892e+000,  4.393889e-001};



const double rad_wsgg::bco2[20]={ 8.425766e-001, -1.442229e+000,  1.286974e+000, -5.202712e-001,  7.581559e-002,
                                 -3.023864e-002,  5.264245e-001, -6.209696e-001,  2.704755e-001, -4.090690e-002,
                                  1.070243e-001, -1.989596e-001,  3.101602e-001, -1.737230e-001,  3.081180e-002,
                                  3.108972e-002,  1.981489e-001, -2.543676e-001,  1.061331e-001, -1.498231e-002 };

const double rad_wsgg::bh2o[20]={ 7.129509e-001, -1.378353e+000,  1.555028e+000, -6.636291e-001,  9.773674e-002,
                                  1.589917e-001,  5.635578e-002,  2.666874e-001, -2.040335e-001,  3.742408e-002,
                                 -1.196373e-001,  1.349665e+000, -1.544797e+000,  6.397595e-001, -9.153650e-002,
                                  3.078250e-001, -6.003555e-001,  4.441261e-001, -1.468813e-001,  1.824702e-002 };

const double rad_wsgg::kco2[5]={0.000000e+000, 3.388079e-002, 4.544269e-001, 4.680226e+000, 1.038439e+002};

const double rad_wsgg::kh2o[5]={0.000000e+000, 7.703541e-002, 8.242941e-001, 6.854761e+000, 6.593653e+001};

///////////////////////////////////////////////////////////////////////////////
/** **This is the class interface function**
 *  Given the gas state, set the k and a vectors.
 *  These can then be accessed by the user.
 *  return through arg list the local gray gas coefficients (kabs) and the local weights (awts).
 *  @param kabs           \output absorption coefficient (1/m) for band/gas iband: ranges from 0 to nGG inclusive
 *  @param awts           \output weight (unitless; total sums to 1) for band/gas iband: ranges from 0 to nGG inclusive
 *  @param iband          \input which band to compute
 *  @param T_dmb          \input gas temperature (K)
 *  @param P              \input pressure (Pa)
 *  @param fvsoot         \input soot volume fraction = rho*Ysoot/rhosoot
 *  @param xH2O           \input mole fraction H2O
 *  @param xCO2           \input mole fraction CO2
 *  @param xCO_not_used   \input mole fraction CO     HERE FOR THE INTERFACE, NOT USED (... pass in 0.0)
 *  @param xCH4_not_used  \input mole fraction CH4    HERE FOR THE INTERFACE, NOT USED (... pass in 0.0)
 * 
 *  See documentation for rad_rcslw::F_albdf_soot for details about the soot absorption coefficient.
 * 
 *     \f$k_{soot} = F_s fv_{soot}T\f$, where \f$F_s = 3.72 c_{soot}/C_2\f$, where \f$C_2 = 0.014388\, m\cdot K\f$ and
 *             \f$c_{soot} = 36\pi n k/[(n^2 - k^2 +2)^2 + 4 (n k)^2],\f$
 *             where \f$k\f$ is the real part of the complex refractive index, and \f$n\f$ is the imaginary part.
 *             Using Shaddix's model for \f$k\f$, \f$n\f$: \f$k=1.03\f$, \f$n = 1.75\f$, giving \f$F_s = 1817\, K^{-1}m^{-1}\f$.
 *             Reference: Williams, Shaddix, et al. Int. J. Heat and Mass Transfer <a href="https://www.sciencedirect.com/science/article/pii/S0017931006004893" target="_blank">50:1616-1630</a> (2007), 
 * 
 * Note, combining the WSGG model with four gray gases and one clear gas with a single gray soot component.
 * The soot absorption coefficient is added to that for each gas (including the clear gas, since
 *     the soot absorption spectrum is "full"). The weights don't need to be changed.
 * In the limit of no soot, we recover gas only, and in the limit of only soot, we recover the expected
 *     behavior. 
 * 
 * \f$dI_j/ds = (kg_j + ks)I_j + (kg_j+ks)a_jIb\f$
 * 
 * This soot addition was suggested by H. Bordbar.
 */

void rad_wsgg::get_k_a_oneband(double       &kabs,
                               double       &awts,
                               const int    iband,
                               const double T_dmb,
                               const double P,
                               const double fvsoot,
                               const double xH2O,
                               const double xCO2,
                               const double xCO_not_used,
                               const double xCH4_not_used){

    if(iband < 0 || iband >= nGGa) {
        cerr << "\n\n***** ERROR rad_wsgg::get_k_a_oneband: iband out of range *****\n" << endl;
        exit(0); 
    }

#ifdef MODEL_BOUNDS_WARININGS
    if(T_dmb < 300.0 || T_dmb > 2400.0)
        cerr << "\n***** WARNING rad_rcslw::get_k_a_oneband: T is out of range 300-2500 K *****\n" << endl;
#endif
#ifdef MODEL_BOUNDS_ERRORS
    if(T_dmb < 300.0 || T_dmb > 2400.0)
        exit(0);
#endif

    //------------------------

    double Mr = xH2O/(xCO2+1E-10);
    double MrOrig = Mr;
    if(Mr < 0.01) Mr = 0.01;
    if(Mr > 4.0)  Mr = 4.0;
    if(MrOrig > 1E8) MrOrig = 1E8;

    double T = T_dmb;
    //if(T<500)  T = 500;       // 500 is in the 2014 paper, but 300 is used in Fig. 2 of the 2020 paper.kjk0
    if(T<300)  T = 300;
    if(T>2400) T = 2400;

    double Tr = T/1200;

    //-------------- 

    const int ni  = 4;
    const int nj  = 5;
    const int nk  = 5;

    int off;                    // index offset

    //------------- kabs

    if(iband==0)
        kabs = 0.0;
    else{
        off = (iband-1)*nk;
        kabs = dCoefs[off+0] + Mr*(dCoefs[off+1] + Mr*(dCoefs[off+2] + Mr*(dCoefs[off+3] + Mr*(dCoefs[off+4]))));
        kabs *= (P/101325)*(xH2O+xCO2);
    }

    //------------- awts

    int njnk = nj*nk;
    int injnk;
    if(iband==0){
        awts = 1.0;
        vector<double> b(nj,0.0);
        for(int i=0; i<ni; i++) {
            injnk = i*njnk;
            for(int j=0; j<nj; j++){
                off = injnk + j*nk;
                b[j] = cCoefs[off+0] + Mr*(cCoefs[off+1] + Mr*(cCoefs[off+2] + Mr*(cCoefs[off+3] + Mr*(cCoefs[off+4])))); // notationally, cCoefs terms are like cCoefs[i][j][k] where k is +0,+1,etc.
            }
            awts -= b[0] + Tr*(b[1] + Tr*(b[2] + Tr*(b[3] + Tr*(b[4]))));
        }
    }
    else{
        injnk = (iband-1)*njnk;
        vector<double> b(nj,0.0);
        for(int j=0; j<nj; j++){
            off = injnk + j*nk;
            b[j] = cCoefs[off+0] + Mr*(cCoefs[off+1] + Mr*(cCoefs[off+2] + Mr*(cCoefs[off+3] + Mr*(cCoefs[off+4])))); // notationally, cCoefs terms are like cCoefs[i][j][k] where k is +0,+1,etc.
        }
        awts = b[0] + Tr*(b[1] + Tr*(b[2] + Tr*(b[3] + Tr*(b[4]))));
    }

    //------------- if Mr < 0.01 linear interp k, a between those bounds and the pure component

    if(MrOrig < 0.01){                      // High CO2 low H2O

        double f = (0.01-MrOrig)/0.01;                 // convenience variable
        double pfac = P/101325*xCO2;

        //---------- kabs

        kabs = kco2[iband]*pfac*(f) + kabs*(1.0-f);

        //---------- awts

        double aco2;
        if(iband==0){
            aco2 = 1.0;
            for(int i=1; i<nGGa; i++){
                off = nj*(i-1);
                aco2 -= bco2[off+0] + Tr*(bco2[off+1] + Tr*(bco2[off+2] + Tr*(bco2[off+3] + Tr*(bco2[off+4]))));
            }
        }
        else{
            off = nj*(iband-1);
            aco2 = bco2[off+0] + Tr*(bco2[off+1] + Tr*(bco2[off+2] + Tr*(bco2[off+3] + Tr*(bco2[off+4]))));
        }
        awts = aco2*(f) + awts*(1.0-f);
    }

    //------------- if Mr > 0.4, linear interp k, a between those bounds and the pure component

    if(MrOrig > 4.0){                         // High H2O low CO2

        double f = (1E8-MrOrig)/(1E8-4.0);             // convenience variable
        double pfac = P/101325*xH2O;

        //---------- kabs

        kabs = kabs*(f) + kh2o[iband]*pfac*(1.0-f);

        //---------- awts

        double ah2o;
        if(iband==0){
            ah2o = 1.0;
            for(int i=1; i<nGGa; i++){
                off = nj*(i-1);
                ah2o -= bh2o[off+0] + Tr*(bh2o[off+1] + Tr*(bh2o[off+2] + Tr*(bh2o[off+3] + Tr*(bh2o[off+4]))));
            }
        }
        else{
            off = nj*(iband-1);
            ah2o = bh2o[off+0] + Tr*(bh2o[off+1] + Tr*(bh2o[off+2] + Tr*(bh2o[off+3] + Tr*(bh2o[off+4]))));
        }
        awts = awts*(f) + ah2o*(1.0-f);
    }

    //--------------------- soot contribution: add ksoot to all gases including the clear gas

    if(fvsoot > 0.0){
        double ksoot= 1817 * fvsoot*T;       // 1817 = 3.72*csoot/C2.
        kabs += ksoot;
    }

    return;
}

///////////////////////////////////////////////////////////////////////////////
/** **This is the class interface function**
 *  Given the gas state, set the k and a vectors.
 *  These can then be accessed by the user.
 *  return through arg list the local gray gas coefficients (kabs) and the local weights (awts).
 *  @param kabs          \output absorption coefficients (1/m) for nGG+1 (nGG gray gases + clear gas)
 *  @param awts          \output weights (unitless; sums to 1) for nGG+1 (nGG gray gases + clear gas)
 *  @param T_dmb         \input gas temperature (K)
 *  @param P             \input pressure (Pa)
 *  @param fvsoot        \input soot volume fraction = rho*Ysoot/rhosoot
 *  @param xH2O          \input mole fraction H2O
 *  @param xCO2          \input mole fraction CO2
 *  @param xCO_not_used  \input mole fraction CO     HERE FOR THE INTERFACE, NOT USED (... pass in 0.0)
 *  @param xCH4_not_used \input mole fraction CH4    HERE FOR THE INTERFACE, NOT USED (... pass in 0.0)
 * 
 *  See documentation for rad_rcslw::F_albdf_soot for details about the soot absorption coefficient.
 * 
 *     \f$k_{soot} = F_s fv_{soot}T\f$, where \f$F_s = 3.72 c_{soot}/C_2\f$, where \f$C_2 = 0.014388\, m\cdot K\f$ and
 *             \f$c_{soot} = 36\pi n k/[(n^2 - k^2 +2)^2 + 4 (n k)^2],\f$
 *             where \f$k\f$ is the real part of the complex refractive index, and \f$n\f$ is the imaginary part.
 *             Using Shaddix's model for \f$k\f$, \f$n\f$: \f$k=1.03\f$, \f$n = 1.75\f$, giving \f$F_s = 1817\, K^{-1}m^{-1}\f$.
 *             Reference: Williams, Shaddix, et al. Int. J. Heat and Mass Transfer <a href="https://www.sciencedirect.com/science/article/pii/S0017931006004893" target="_blank">50:1616-1630</a> (2007), 
 * 
 * Note, combining the WSGG model with four gray gases and one clear gas with a single gray soot component.
 * The soot absorption coefficient is added to that for each gas (including the clear gas, since
 *     the soot absorption spectrum is "full"). The weights don't need to be changed.
 * In the limit of no soot, we recover gas only, and in the limit of only soot, we recover the expected
 *     behavior. 
 * 
 * \f$dI_j/ds = (kg_j + ks)I_j + (kg_j+ks)a_jIb\f$
 * 
 * This soot addition was suggested by H. Bordbar.
 */

void rad_wsgg::get_k_a(vector<double> &kabs,
                       vector<double> &awts,
                       const double   T_dmb,
                       const double   P,
                       const double   fvsoot,
                       const double   xH2O,
                       const double   xCO2,
                       const double   xCO_not_used,
                       const double   xCH4_not_used){

    //------------------------

    kabs.resize(nGGa);
    awts.resize(nGGa);

    double k, a;
    for(int i=0; i<nGGa; i++){
        get_k_a_oneband(k, a, i, T_dmb, P, fvsoot, xH2O, xCO2, xCO_not_used, xCH4_not_used);
        kabs[i] = k;
        awts[i] = a;
    }

    return;
}