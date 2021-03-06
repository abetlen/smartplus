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

///@file contimech.hpp
///@brief Functions that computes Mises stress/strains, directions, etc
///@version 1.0

#pragma once
#include <armadillo>

namespace smart{

//This function returns the trace of the tensor v
double tr(const arma::vec &);

//This function returns the deviatoric part of v
arma::vec dev(const arma::vec &);

//This function determines the Mises equivalent of a stress tensor, according to the Voigt convention for stress 
double Mises_stress(const arma::vec &);

//This function determines the strain flow (direction) from a stress tensor, according to the Voigt convention for strains
arma::vec eta_stress(const arma::vec &);

//This function determines the Mises equivalent of a strain tensor, according to the Voigt convention for strains 
double Mises_strain(const arma::vec &);

//This function determines the strain flow (direction) from a strain tensor, according to the Voigt convention for strains
arma::vec eta_strain(const arma::vec &);

//This function transforms the strain Voigt vector into a 3*3 strain matrix
arma::mat v2t_strain(const arma::vec &v);

//This function transforms a 3*3 strain matrix into a strain Voigt vector
arma::vec t2v_strain (const arma::mat &);

//This function transforms the stress Voigt vector into a 3*3 stress matrix
arma::mat v2t_stress(const arma::vec &);

//This function transforms a 3*3 stress matrix into a stress Voigt vector
arma::vec t2v_stress (const arma::mat &);

//Returns the second invariant of the deviatoric part of a second order stress tensor written as a Voigt vector
double J2_stress(const arma::vec &);

//Returns the second invariant of the deviatoric part of a second order strain tensor written as a Voigt vector
double J2_strain(const arma::vec &);

//Returns the third invariant of the deviatoric part of a second order stress tensor written as a Voigt vector
double J3_stress(const arma::vec &);

//Returns the third invariant of the deviatoric part of a second order stress tensor written as a Voigt vector
double J3_strain(const arma::vec &);

//This function returns the value if it's positive, zero if it's negative (Macaulay brackets <>+)
double Macaulay_p(const double &);

//This function returns the value if it's negative, zero if it's positive (Macaulay brackets <>-)
double Macaulay_n(const double &);

//This function returns the value if it's negative, zero if it's positive (Macaulay brackets <>-)
double sign(const double &);
    
//Returns the normalized vector normal to an ellipsoid with semi-principal axes of length a1, a2, a3. The direction of the normalized vector is set by angles u
arma::vec normal_ellipsoid(const double &, const double &, const double &, const double &, const double &);

//Returns the curvature of an ellipsoid with semi-principal axes of length a1, a2, a3 at the angle u,v.
double curvature_ellipsoid(const double &, const double &, const double &, const double &, const double &);

//Returns the normal and tangent components of the stress vector in the normal direction n to an ellipsoid with axes a1, a2, a3. The direction of the normalized vector is set by angles u
arma::vec sigma_int(const arma::vec &, const double &, const double &, const double &, const double &, const double &);

///This computes the Hill interfacial operator according to a normal a (see papers of Siredey and Entemeyer phD dissertation)
arma::mat p_ikjl(const arma::vec &);

} //namespace smart
