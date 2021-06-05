/**
 *  @file simple_interface.cc
 *  \brief Simple interface: demonstrate calling library for one gas state
 */

#include <vector>
#include <iostream>
#include <iomanip>
#include "../../src/c++/rad_planck_mean.h"
#include "../../src/c++/rad_wsgg.h"
#include "../../src/c++/rad_rcslw.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////

int main() {

    //----------------- define parameters

    double T      = 2000.0;    // K
    double P      = 101325.0;  // atm
    double xH2O   = 0.8;       // xH2O=0.2 is roughly stoich. CH4/air products
    double xCO2   = 0.2;       // xCO2=0.1 is roughly stoich. CH4/air products
    double xCO    = 0.;
    double xCH4   = 0.;
    double fvsoot = 0.;

    vector<double> kabs_pm, kabs_wsgg, kabs_rcslw;
    vector<double> awts_pm, awts_wsgg, awts_rcslw;

    //----------------- create radiation objects

    rad *planckmean = new rad_planck_mean();
    rad *wsgg       = new rad_wsgg();
    rad *rcslw      = new rad_rcslw(4, P, T, xH2O, xCO2, xCO, fvsoot);

    //----------------- compute absorption coefficients and weights

    planckmean->get_k_a(T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_pm,    awts_pm);
    wsgg->get_k_a(      T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_wsgg,  awts_wsgg);
    rcslw->get_k_a(     T, P, xH2O, xCO2, xCO, xCH4, fvsoot, kabs_rcslw, awts_rcslw);

    //----------------- output results

    cout << setprecision(3) << fixed;

    cout << endl << "T (K)  = " << setw(14) << T;
    cout << endl << "P (Pa) = " << setw(14) << P;
    cout << endl << "xH2O   = " << setw(14) << xH2O;
    cout << endl << "xCO2   = " << setw(14) << xCO2;
    cout << endl << "xCO    = " << setw(14) << xCO;
    cout << endl << "xCH4   = " << setw(14) << xCH4;
    cout << endl;

    cout << setprecision(8) << fixed;

    cout << endl;
    cout << endl << "Planck Mean:";
    cout << endl << "   kabs (1/m),   awts";
    for(int i=0; i<kabs_pm.size(); i++)
        cout << endl << setw(14) << kabs_pm[i] << setw(14) << awts_pm[i];

    cout << endl;
    cout << endl << "WSGG:";
    cout << endl << "   kabs (1/m),   awts";
    for(int i=0; i<kabs_wsgg.size(); i++)
        cout << endl << setw(14) << kabs_wsgg[i] << setw(14) << awts_wsgg[i];

    cout << endl;
    cout << endl << "RCSLW:";
    cout << endl << "   kabs (1/m),   awts";
    for(int i=0; i<kabs_rcslw.size(); i++)
        cout << endl << setw(14) << kabs_rcslw[i] << setw(14) << awts_rcslw[i];

    return 0;

    //----------------- cleanup

    delete planckmean;
    delete wsgg;
    delete rcslw;

}
