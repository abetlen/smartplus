/* This file is part of SMART+.
 
 SMART+ is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 SMART+ is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with SMART+.  If not, see <http://www.gnu.org/licenses/>.
 
 */

///@file step.hpp
///@brief object that defines an step
///@version 1.0

#pragma once

#include <iostream>
#include <armadillo>
#include "output.hpp"
#include "../Phase/state_variables.hpp"
#include "../Phase/phase_characteristics.hpp"

namespace smart{

//======================================
class step
//======================================
{
private:
    
protected:
    
	public :
    int number;     //Number of the step
    double Dn_init;    //Initial fraction of the step
    double Dn_mini;    //Minimal fraction of the step
    double Dn_inc;    //Maximal fraction of the step
    int ninc;       //Number of milestones in the step (based on Dnmaxi)
    int mode;
    
    arma::vec times;
    double BC_Time;
    
    std::string file; //  It is used for input/output values of the loading path
    
    step(); 	//default constructor
    step(const int &, const double &, const double &, const double &, const int &);	//Constructor with parameters
    step(const step &);	//Copy constructor
    virtual ~step();
   
    virtual void generate();
    virtual void compute_inc(double &, const int &, double &, double &, double &);
    virtual void assess_inc(const double &, double &, const double &, phase_characteristics &, double &, const double &);
    
    virtual step& operator = (const step&);
    
    friend  std::ostream& operator << (std::ostream&, const step&);
};

} //namespace smart
