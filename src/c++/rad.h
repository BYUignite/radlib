/**
 * @file rad.h
 * Header file for class rad
 * \brief Abstract base class
 */

#ifndef RAD_H
#define RAD_H

#pragma once

#include <vector>

////////////////////////////////////////////////////////////////////////////////

/** Class implementing rad object.
 * Abstract base class upon which specific radiation property models are built.
 * get_k_a is the primary interface.
 */

class rad {


    //////////////////// DATA MEMBERS //////////////////////

    public: 

        constexpr static double sigma = 5.670367E-8;    ///< Stephan-Boltzmann constant

    protected:

        int    nGG;                           ///< number of gray gases, not including the clear gas
        int    nGGa;                          ///< number of grey gases including the clear gas


    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void get_k_a(const double   T,             ///< gas temperature (K)
                             const double   P,             ///< gas pressure (Pa)
                             const double   xH2O,          ///< mole fraction h2o
                             const double   xCO2,          ///< mole fraction co2
                             const double   xCO,           ///< mole fraction co
                             const double   xCH4,          ///< mole fraction ch4
                             const double   fvsoot,        ///< volume fraction soot (not ppmv)
                             std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                             std::vector<double> &awts)    ///< gas weight (sum to one)
                             = 0;                          ///< ABSTRACT BASE CLASS 

        int get_nGG(){ return nGG; }
        int get_nGGa(){return nGGa; }

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad(const int p_nGG, const int p_nGGa) {
                nGG  = p_nGG;
                nGGa = p_nGGa;
        }

        virtual ~rad(){}

};

#endif //RADLIB_H