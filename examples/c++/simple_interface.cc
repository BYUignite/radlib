#include "rad_planck_mean.h"
#include "rad_wsgg.h"
#include "rad_rcslw.h"
#include <vector>
#include <iostream>
#include <iomanip>

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

    cout << endl << "T (K)  = " << T;
    cout << endl << "P (Pa) = " << P;
    cout << endl << "xH2O   = " << xH2O;
    cout << endl << "xCO2   = " << xCO2;
    cout << endl << "xCO    = " << xCO;
    cout << endl << "xCH4   = " << xCH4;
    cout << endl;

    cout << endl << "Planck Mean:";
    cout << endl << "   kabs (1/m) = " << setw(12) << kabs_pm[0];
    for(int i=1; i<kabs_pm.size(); i++)
        cout << ", " << setw(12) << kabs_pm[i];
    cout << endl << "   awts       = " << setw(12) << awts_pm[0];
    for(int i=1; i<awts_pm.size(); i++)
        cout << ", " << setw(12) << awts_pm[i];

    cout << endl << "WSGG:";
    cout << endl << "   kabs (1/m) = " << setw(12) << kabs_wsgg[0];
    for(int i=1; i<kabs_wsgg.size(); i++)
        cout << ", " << setw(12) << kabs_wsgg[i];
    cout << endl << "   awts       = " << setw(12) << awts_wsgg[0];
    for(int i=1; i<awts_wsgg.size(); i++)
        cout << ", " << setw(12) << awts_wsgg[i];

    cout << endl << "RCSLW:";
    cout << endl << "   kabs (1/m) = " << setw(12) << kabs_rcslw[0];
    for(int i=1; i<kabs_rcslw.size(); i++)
        cout << ", " << setw(12) << kabs_rcslw[i];
    cout << endl << "   awts       = " << setw(12) << awts_rcslw[0];
    for(int i=1; i<awts_rcslw.size(); i++)
        cout << ", " << setw(12) << awts_rcslw[i];

    return 0;

    //----------------- cleanup

    delete planckmean;
    delete wsgg;
    delete rcslw;

}
