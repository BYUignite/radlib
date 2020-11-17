#include <iostream>
#include <cmath>         // M_PI
#include "rad_rcslw.h"
#include "rad.h"

using namespace std;

void parallel_planes(rad                  *RAD,
                     const double         L,
                     const int            ntheta,
                     const double         P, 
                     const vector<double> &T,
                     const vector<double> &xH2O,
                     const vector<double> &xCO2,
                     const vector<double> &xCO,
                     const vector<double> &xCH4,
                     const vector<double> &fvsoot,
                     vector<double>       &q,
                     vector<double>       &Q,
                     vector<double>       &x,
                     vector<double>       &xQ,
                     const bool           LzeroIbc=false
                     );

///////////////////////////////////////////////////////////////////////////////

int main() {

    //--------------------- parameters

    double P      = 101325.0;
    double L      = 2.0;
    int    nGG    = 25;
    int    ntheta = 101;
    int    nx     = 1001;
    double T0     = 1500;
    double TL     = 500;

    int    nGGa   = nGG+1;

    double TT=1500, xco2=0.0, xco=0.0, xh2o=0.1, fvs=0.0;

    //---------------------

    vector<double> xCO2(nx, xco2);
    vector<double> xCO(nx, xco);
    vector<double> xH2O(nx, xh2o);
    vector<double> xCH4(nx, 0.0);
    vector<double> fvsoot(nx, fvs);

    vector<double> x(nx, 0.0);
    vector<double> xQ;
    vector<double> T(nx, T0);

    double dx = L/(nx-1);
    x[0] = 0.0;
    double Tavg = T[0];
    for(int i=1; i<nx; ++i){
        x[i] = x[i-1] + dx;
        T[i] = 1000.0 + 500*cos(M_PI*x[i]/L);
        Tavg += T[i];
    }
    Tavg /= nx;

    //rad *rcslw = new rad_rcslw(nGG, P, Tavg, xh2o, xco2, xco, fvs); // TT gives better results than Tavg 
    rad *rcslw = new rad_rcslw(nGG, P, TT, xh2o, xco2, xco, fvs);     // TT gives better results than Tavg 

    //--------------------- get q, Q

    vector<double> q;    
    vector<double> Q;

    parallel_planes(rcslw, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ);

    //-------------------------------------------------------------------------

    cout << "# x (m), Q (kW/m3)";
    for(int i=0; i<xQ.size(); ++i)
        cout << endl << xQ[i] << "  " << Q[i]/1000;

    //cout << "# x (m), q (kW/m2)";
    //for(int i=0; i<x.size(); ++i)
    //    cout << endl << x[i] << "  " << q[i]/1000;

    cout << endl;
    
    return 0;

}

