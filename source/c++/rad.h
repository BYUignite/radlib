/**
 * @file rad.h
 * Header file for class rad
 * Abstract base class
 */

#pragma once

#include <vector>
#include <iostream>
#include <cstdlib>

////////////////////////////////////////////////////////////////////////////////

/** Class implementing rad object
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

        virtual void get_k_a(const double   T,             ///< for WSGG
                             const double   P,
                             const double   xH2O,
                             const double   xCO2,
                             std::vector<double> &kabs,
                             std::vector<double> &awts){
            std::cout << std::endl << "rad::get_k_a function being called is not implemented" << std::endl;
            exit(0);
        }

        virtual void get_k_a(const double   T,             ///< for RCSLW
                             const double   xH2O,
                             const double   xCO2,
                             const double   xCO,
                             const double   fvsoot,
                             std::vector<double> &kabs,
                             std::vector<double> &awts){
            std::cout << std::endl << "rad::get_k_a function being called is not implemented" << std::endl;
            exit(0);
        }

        int get_nGG(){ return nGG; }
        int get_nGGa(){return nGGa; }

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad(const int p_nGG,
            const int p_nGGa){ 
            nGG  = p_nGG;
            nGGa = p_nGGa;
        }

        virtual ~rad(){}


};
