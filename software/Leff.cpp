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

///@file constitutive.hpp
///@brief solver: solve the mechanical thermomechanical equilibrium			//
//	for a homogeneous loading path, allowing repeatable steps
///@version 1.9

#include <iostream>
#include <fstream>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <armadillo>
#include <smartplus/parameter.hpp>
#include <smartplus/Umat/umat_L_elastic.hpp>
#include <smartplus/Libraries/Solver/read.hpp>
#include <smartplus/Libraries/Phase/state_variables_M.hpp>
#include <smartplus/Libraries/Phase/phase_characteristics.hpp>

using namespace std;
using namespace arma;
using namespace smart;

ofstream output("L.txt");

int main() {
    
	///Material properties reading, use "material.dat" to specify parameters values
    string umat_name;
    string path_data = "data";
    string materialfile = "material.dat";
	
    int nprops = 0;
    int nstatev = 0;
    vec props;
    
    double psi_rve = 0.;
    double theta_rve = 0.;
    double phi_rve = 0.;
    
    double T_init = 273.15;

    read_matprops(umat_name, nprops, props, nstatev, psi_rve, theta_rve, phi_rve, path_data, materialfile);
    phase_characteristics rve;
    
    rve.sptr_matprops->update(0, umat_name, 1, psi_rve, theta_rve, phi_rve, props.n_elem, props);
    rve.construct(0,1);
    rve.sptr_sv_global->update(zeros(6), zeros(6), zeros(6), zeros(6), T_init, 0., nstatev, zeros(nstatev), zeros(nstatev));
    
    auto sv_M = std::dynamic_pointer_cast<state_variables_M>(rve.sptr_sv_global);

    //Second we call a recursive method that find all the elastic moduli iof the phases
    get_L_elastic(rve);
    output << sv_M->Lt << "\n";
    
	return 0;
}
