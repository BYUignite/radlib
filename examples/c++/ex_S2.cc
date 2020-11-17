#include <iostream>
#include <cmath>         // pow
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

    double TT     = 1000.0;
    double P      = 101325.0;
    double xco2_1 = 0.4;
    double xco2_2 = 0.1;
    double Lhot   = 0.5;
    int    nGG    = 24;
    int    ntheta = 101;
    int    nxh    = 1001;    // for Lcold=0; changes below to keep dx roughly constant

    vector<double> Lcold{0, 0.01, 0.025, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.75, 1.0, 1.5, 2.0};

    int    nGGa   = nGG+1;

    double xco=0.0, xh2o=0.0, xch4=0.0, fvs=0.0;

    //---------------------

    cout << "# Lcold (m), q(L)/σThot^4";

    for(int iLcold=0; iLcold<Lcold.size(); ++iLcold){

        double L  = Lcold[iLcold] + Lhot;

        double xco2_avg = (xco2_1*0.5+xco2_2*Lcold[iLcold])/L;

        int nx = int(nxh*L/Lhot);

        vector<double> xCO2(nx, xco2_1);
        vector<double> xCO(nx, xco);
        vector<double> xH2O(nx, xh2o);
        vector<double> xCH4(nx, 0.0);
        vector<double> fvsoot(nx, fvs);

        vector<double> x(nx, 0.0);
        vector<double> xQ;
        vector<double> T(nx, TT);

        double dx = L/(nx-1);
        x[0] = 0.0;
        for(int i=1; i<nx; ++i){
            x[i] = x[i-1] + dx;
            xCO2[i] = (x[i]<=Lhot) ? xco2_1 : xco2_2;
        }

        rad *rcslw = new rad_rcslw(nGG, P, TT, xh2o, xco2_avg, xco, fvs);

        //--------------------- get q, Q

        vector<double> q;    
        vector<double> Q;

        parallel_planes(rcslw, L, ntheta, P, T, xH2O, xCO2, xCO, xCH4, fvsoot, q, Q, x, xQ, true);

        //-------------------------------------------------------------------------

        cout << endl << Lcold[iLcold] << "  " << q[nx-1]/rad::sigma/pow(TT,4.0);

    } // end loop over Lcold

    cout << endl;
    
    return 0;

}

