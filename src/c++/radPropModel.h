/**
 * @file radPropModel.h
 * Header file for class radPropModel
 * \brief Abstract base class
 */

#ifndef RADPROPMODEL_H
#define RADPROPMODEL_H

#pragma once

#include <vector>

////////////////////////////////////////////////////////////////////////////////

/** Class implementing radPropModel object.
 * Abstract base class upon which specific radiation property models are built.
 * get_k_a, and get_k_a_oneband are the primary interfaces.
 */

class radPropModel {


    //////////////////// DATA MEMBERS //////////////////////

    public: 

        constexpr static double sigma = 5.670367E-8;    ///< Stephan-Boltzmann constant

    protected:

        int    nGG;                           ///< number of gray gases, not including the clear gas
        int    nGGa;                          ///< number of grey gases including the clear gas


    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        virtual void get_k_a(std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                             std::vector<double> &awts,    ///< gas weight (sum to one)
                             const double   T,             ///< gas temperature (K)
                             const double   P,             ///< gas pressure (Pa)
                             const double   fvsoot,        ///< volume fraction soot (not ppmv)
                             const double   xH2O,          ///< mole fraction h2o
                             const double   xCO2,          ///< mole fraction co2
                             const double   xCO=0,         ///< mole fraction co
                             const double   xCH4=0)        ///< mole fraction ch4
                             = 0;                          ///< ABSTRACT BASE CLASS 

        virtual void get_k_a_oneband(double         &kabs,   ///< absorption coefficient (1/m)
                                     double         &awts,   ///< gas weight (sum to one)
                                     const int      iband,   ///< band/gas to get k_a for
                                     const double   T,       ///< gas temperature (K)
                                     const double   P,       ///< gas pressure (Pa)
                                     const double   fvsoot,  ///< volume fraction soot (not ppmv)
                                     const double   xH2O,    ///< mole fraction h2o
                                     const double   xCO2,    ///< mole fraction co2
                                     const double   xCO=0,   ///< mole fraction co
                                     const double   xCH4=0)  ///< mole fraction ch4
                                     = 0;                    ///< ABSTRACT BASE CLASS 

        int get_nGG(){ return nGG; }
        int get_nGGa(){return nGGa; }

    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        radPropModel(const int p_nGG, const int p_nGGa) {
            nGG  = p_nGG;
            nGGa = p_nGGa;
        }

        virtual ~radPropModel(){}

};

#endif //RADPROPMODEL_H