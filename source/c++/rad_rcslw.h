/**
 * @file rad_rcslw.h
 * Header file for class rad_rcslw
 */

#pragma once

#include <string>
#include <vector> 
#include "rad.h"

////////////////////////////////////////////////////////////////////////////////

/** Class implementing rcslw object
 */

class rad_rcslw : public rad {


    //////////////////// DATA MEMBERS //////////////////////

    protected:

        double       P;                   ///< system pressure (atm); assumed constant
        double       Tref;                ///< reference temperature (K) for setting F grid (normally same as Tb)
        double       Tb;                  ///< black temperature (K)

        std::vector<double> P_table;      ///< pressures (atm, abscissas) in table
        std::vector<double> C_table;      ///< cross sections (m2/mol abscissas) in table
        std::vector<double> Tg_table;     ///< gas temperatures (K, abscissas) in table
        std::vector<double> Tb_table;     ///< blackbody temperature (K, abscissas) in table
        std::vector<double> xH2O_table;   ///< mole fractions H2O (abscissas) in table

        std::vector<double> F_pts;        ///< albdf grid 
        std::vector<double> Ft_pts;       ///< albdf grid (t for tilde)

        std::vector<double> Falbdf_CO2;   ///< CO2 albdf table values (with abscissas above)
        std::vector<double> Falbdf_CO;    ///< CO  albdf table values
        std::vector<double> Falbdf_H2O;   ///< H2O albdf table values

        int nP;                           ///< number of P values   (abscissas) in table
        int nC;                           ///< number of C values   (abscissas) in table
        int nTg;                          ///< number of Tg values  (abscissas) in table
        int nTb;                          ///< number of Tb values  (abscissas) in table
        int ny_H2O;                       ///< number of h2o values (abscissas) in table

        double Cmin;                      ///< minimum absorption cross section
        double Cmax;                      ///< maximum absorption cross section
        double Fmin;                      ///< minimum albdf, corresponding to Cmin
        double Fmax;                      ///< maximum albdf, corresponding to Cmax

    //////////////////// MEMBER FUNCTIONS /////////////////

    public:

        //-------------- primary interface (note, P is set in constructor)

        void get_k_a(const double   T,             ///< gas temperature (K)
                     const double   xH2O,          ///< mole fraction H2O
                     const double   xCO2,          ///< mole fraction CO2
                     const double   xCO,           ///< mole fraction CO
                     const double   fvsoot,        ///< volume fraction soot (not ppmv)
                     std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                     std::vector<double> &awts);   ///< gas weight (sum to one)

        //-------------- implementation of pure virtual abstract base class function
        //-------------- just calls the primary interface

        void get_k_a(const double   T,             ///< gas temperature (K)
                     const double   P_not_used,    ///< gas pressure (Pa); (interface only, set by constructor)
                     const double   xH2O,          ///< mole fraction H2O
                     const double   xCO2,          ///< mole fraction CO2
                     const double   xCO,           ///< mole fraction CO
                     const double   xCH4_not_used, ///< mole fraction CH4 (interface only, not used)
                     const double   fvsoot,        ///< volume fraction soot (not ppmv)
                     std::vector<double> &kabs,    ///< absorption coefficient (1/m)
                     std::vector<double> &awts){   ///< gas weight (sum to one)
            get_k_a(T, xH2O, xCO2, xCO, fvsoot, kabs, awts);
        }

    private:

        double get_F_albdf(const double C, double Tg, double Tb, double xCO2, double xCO, double xH2O,
                           double fvsoot);
        double get_FI_albdf(const double F, const double Tg, const double Tb, 
                            const double xCO2, const double xCO, const double xH2O,
                            const double fvsoot);
        void get_FI_albdf_tables(const std::string Ptable_file_name, 
                                 const int nx, const int ny, const int nz,
                                 std::vector<double> &myarray);
        void get_FI_albdf_tables(const std::string Ptable_file_name, 
                                 const int nx, const int ny, const int nz, const int nw,
                                 std::vector<double> &myarray);
        void set_Fpts(void);
        void set_Falbdf_CO2_CO_H2O_at_P();
        double F_albdf_soot(const double C, const double Tg, const double Tb, const double fvsoot);
        
    //////////////////// CONSTRUCTOR FUNCTIONS /////////////////
    
    public: 
    
        rad_rcslw(const int    p_nGG,
                  const double p_P,
                  const double TbTref,
                  const double xH2O,
                  const double xCO2, 
                  const double xCO, 
                  const double fvsoot);

        virtual ~rad_rcslw(){}

};

