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

///@file kinematics.cpp
///@brief A set of function that allows various strain transformation (in Finite strains)
///@version 1.0

#include <iostream>
#include <assert.h>
#include <math.h>
#include <armadillo>

using namespace std;
using namespace arma;

namespace smart{
    
//This function computes the gradient of displacement (Lagrangian) from the deformation gradient tensor
mat G_UdX(const mat &F) {
    return F - eye(3,3);
}

//This function computes the gradient of displacement (Eulerian) from the deformation gradient tensor
mat G_Udx(const mat &F) {
    return eye(3,3) - inv(F);
}
    
//This function computes the Right Cauchy-Green C
mat R_Cauchy_Green(const mat &F) {
    return F.t()*F;
}
    
//This function computes the Left Cauchy-Green B
mat L_Cauchy_Green(const mat &F) {
    return F*F.t();
}
    
//This function computes the common Right (or Left) Cauchy-Green invariants
vec Inv_X(const mat &X) {
    
    vec lambda = eig_sym(X);
    vec I = zeros(3);
    I(0) = trace(X);
    I(1) = pow(trace(X),2.) + trace(X*X);
    I(2) = det(X);
    return I;
}

//This function computes the Cauchy deformation tensor c
mat Cauchy(const mat &F) {
    return inv(L_Cauchy_Green(F));
}
    
//This function computes the Green-Lagrange finite strain tensor E
mat Green_Lagrange(const mat &F) {
    return 0.5*(R_Cauchy_Green(F) - eye(3,3));
}

//This function computes the Euler-Almansi finite strain tensor A
mat Euler_Almansi(const mat &F) {
    return 0.5*(eye(3,3) - Cauchy(F));
}
    
//This function computes the velocity difference
mat finite_L(const mat &F, const mat &DF, const double &DTime) {
    
    //Inverse of F0 and F1: G0 and G1
    mat G=inv(F);
    
    //Definition of L = dot(F)*F^-1
    return (1./DTime)*(DF)*G;
}
    
//This function computes the spin tensor W (correspond to Jaumann rate)
mat finite_W(const mat &F, const mat &DF, const double &DTime) {

    //Inverse of F
    mat G=inv(F);
    
    //Definition of L = dot(F)*F^-1
    mat L=(1./DTime)*(DF)*G;
    
    //Definition of the rotation matrix Q
    return 0.5*(L-L.t());

}
    
//This function computes the spin tensor Omega (corrspond to Green-Naghdi rate)
// Note : here R is the is the rigid body rotation in the polar decomposition of the deformation gradient F
mat finite_Omega(const mat &R, const mat &DR, const double &DTime) {
    
    //Definition of Omega = dot(R)*R^-1 (or R.t() since R is a rotation matrix)
    return (1./DTime)*(DR)*R.t();
}    

//This function computes the deformation rate D
mat finite_D(const mat &F, const mat &DF, const double &DTime) {
    
    //Inverse of F0 and F1: G0 and G1
    mat G=inv(F);
    
    //Definition of L = dot(F)*F^-1
    mat L=(1./DTime)*(DF)*G;
    
    //Definition of the deformation rate D
    return 0.5*(L+L.t());
    
}

//This function computes the increment of finite rotation
mat finite_DQ(const mat &Omega0, const mat &Omega1, const double &DTime) {
    
    return (eye(3,3)+0.5*DTime*Omega0)*(inv(eye(3,3)-0.5*DTime*Omega1));
}

    
    
} //namespace smart
