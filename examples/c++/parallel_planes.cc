#include <cmath>          // M_PI, sin, cos
#include "rad.h"

#include <iostream>   //doldb

using namespace std;

////////////////////////////////////////////////////////////////////////////////

/** Compute intensity at each grid point for a given angle.
 *  Solution using an implicit trapazoid method.
 *  @param x     \input vector of grid points
 *  @param theta \input angle measured: grid between plates aligned with theta=0
 *  @param T     \input vector of temperatures (K)
 *  @param kabs  \input 2D vector of absorption coefficients for each gas [igrid, igas]
 *  @param awts  \input 2D vector of weights for each gas [igrid, igas]
 *  @param Ilo   \input vector of gas intensities on the lower plane.
 *  @param Ihi   \input vector of gas intensities on the upper plane.
 *  @param I     \ouput vector of vector of gas intensities in direction theta [igrid, igas]
 */

void I_IT(const vector<double> &x, 
          const double theta, 
          const vector<double> &T,
          const vector<vector<double>> &kabs,
          const vector<vector<double>> &awts,
          const vector<double> &Ilo, 
          const vector<double> &Ihi, 
          vector<vector<double>> &I){

    int n     = x.size();
    int nGGa  = I[0].size();
    double dx;

    double Ib1, Ib2;
    double mu = abs(cos(theta));

    if(theta <= M_PI/2){
        I[0] = Ilo;
        for(int i=0; i<n-1; ++i){
            Ib1 = rad::sigma/M_PI*pow(T[i+1],4.0);
            Ib2 = rad::sigma/M_PI*pow(T[i],4.0);
            dx  = x[i+1] - x[i];
            //I[i+1][0] = I[0][0];          // do the clear gas intensity
            //for(int j=1; j<nGGa; ++j)     // j=1 skips the clear gas, done in previous line
            for(int j=0; j<nGGa; ++j)       // OR, just do all (needed for Planck mean)
                I[i+1][j] = (I[i][j] + dx/mu*0.5*(kabs[i+1][j]*awts[i+1][j]*Ib1 + kabs[i][j]*(awts[i][j]*Ib2 - I[i][j]))) /
                            (1.0+dx/mu*0.5*kabs[i+1][j]);
        }
    }
    else{
        I[n-1] = Ihi;
        for(int i=n-1; i>0; --i){
            Ib1 = rad::sigma/M_PI*pow(T[i-1],4.0);
            Ib2 = rad::sigma/M_PI*pow(T[i],4.0);
            dx  = x[i] - x[i-1];
            //I[i-1][0] = I[n-1][0];         // do the clear gas intensity
            //for(int j=1; j<nGGa; ++j)      // j=1 skips the clear gas, done in previous line
            for(int j=0; j<nGGa; ++j)        // OR, just do all (needed for Planck mean)
                I[i-1][j] = (I[i][j] + dx/mu*0.5*(kabs[i-1][j]*awts[i-1][j]*Ib1 + kabs[i][j]*(awts[i][j]*Ib2 - I[i][j]))) /
                            (1.0+dx/mu*0.5*kabs[i-1][j]);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

/** Compute radiative heat flux (q) and volumetric heat source (Q) profiles between parallel planes.
 *  Solution using simple ray tracing.
 *  Pass in T, P, composition profiles on equally spaced points including boundaries.
 *  @param RAD      \input radlib object
 *  @param L        \input distance (m) between planes
 *  @param ntheta   \input number of ray angles
 *  @param P        \input system pressure (Pa)
 *  @param T        \input vector of temperatures at each point (K)
 *  @param xH2O     \input vector of H2O mole fractions at each point
 *  @param xCO2     \input vector of CO2 mole fractions at each point
 *  @param xCO      \input vector of CO  mole fractions at each point
 *  @param xCH4     \input vector of CH4 mole fractions at each point
 *  @param fvsoot   \input vector of soot volume fractions at each point
 *  @param q        \output vector of heat fluxes at each point (W/m2)
 *  @param x        \output vector of grid locations (m)
 *  @param xQ       \output vector of Q grid locations (m)
 *  @param LzeroIbc \input bool true to make Ibc=0, false otherwise (default = false)
 */

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
                     ) {

    //--------------------- set the grid of x and array of theta

    double dtheta = M_PI/ntheta;

    vector<double> theta(ntheta, dtheta/2);
    for(int i=1; i<ntheta; ++i)
        theta[i] = theta[i-1] + dtheta;

    int nx = T.size();
    double dx = L/(nx-1);
    x  = vector<double> (nx,  0.0);           // x grid are face values:   |   |   |   |   | 
    xQ = vector<double> (nx-1,0.0);           // xQ grid are cell centers:   *   *   *   *
    for(int i=1; i<x.size(); ++i){
        x[i] = x[i-1] + dx;
        xQ[i-1] = 0.5*(x[i-1] + x[i]);
    }

    //--------------------- initialize radiative properties

    vector<vector<double>> kabs(nx, vector<double>(RAD->get_nGGa()));
    vector<vector<double>> awts(nx, vector<double>(RAD->get_nGGa()));

    for(int i=0; i<nx; ++i)
        RAD->get_k_a(T[i], P, xH2O[i], xCO2[i], xCO[i], xCH4[i], fvsoot[i], kabs[i], awts[i]);

    vector<double> Ilo(RAD->get_nGGa(), 0.0);
    vector<double> Ihi(RAD->get_nGGa(), 0.0);

    for(int j=0; j<Ilo.size(); ++j){
        if(LzeroIbc){
            Ilo[j] = 0.0;
            Ihi[j] = 0.0;
        }
        else{
            Ilo[j] = rad::sigma/M_PI*pow(T[0],     4.0)*awts[0][j];
            Ihi[j] = rad::sigma/M_PI*pow(T.back(), 4.0)*awts[nx-1][j];
        }
    }

    vector<vector<double>> I(nx, vector<double>(RAD->get_nGGa(), 0.0));

    //--------------------- solve for q, Q

    q = vector<double>(nx,   0.0);
    Q = vector<double>(nx-1, 0.0);

    double sumI;

    for(int j=0; j<ntheta; ++j) {
        I_IT(x, theta[j], T, kabs, awts, Ilo, Ihi, I);
        for(int i=0; i<nx; ++i) {
            sumI = 0.0;
            for(int k=0; k<RAD->get_nGGa(); ++k)
                sumI += I[i][k];
            q[i] += 2.0*M_PI*dtheta*cos(theta[j])*sin(theta[j])*sumI;
        }
    }

    for(int i=0; i<nx-1; i++)
        Q[i] = -(q[i+1]-q[i])/dx;

}
