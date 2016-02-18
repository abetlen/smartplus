/* This file is part of SMART+ private.
 
 Only part of SMART+ is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This file is not be distributed under the terms of the GNU GPL 3.
 It is a proprietary file, copyrighted by the authors
 */

///@file individual.hpp
///@brief individual for genetic algorithm (among others)
///@author Chemisky & Despringre
///@version 1.0

#pragma once

#include <iostream>
#include <armadillo>
#include "parameters.hpp"
#include "individual.hpp"
#include "opti_data.hpp"

namespace smart{

///This function constructs the vector of exp/num
arma::vec calcV(std::vector<opti_data> &, const int &, const int &);

///This function constructs the sensitivity matrix
void calcS(const individual &, arma::mat &, const arma::vec &, const std::vector<opti_data> &, const int &, const int &, const double &);

///This function checks the sensitivity matrix.
///This ensures that if a parameter didn't modify at all the result, the sensibility matrix doesn't have a column of "0" (inversion) issues
arma::Col<int> checkS(arma::mat &);

///This function computes the Cost function (Square differnces) from the components of experimental values and numerically evaluated values 
double calcC(const arma::vec &, const arma::vec &, const arma::vec &);

//This function computes the approximation of Hessian for under quadratic form assumptions, according to a weight vector
arma::mat Hessian(const int &, const arma::mat &, const arma::vec &);
    
//This function computes the diagonal of the Hessian, which is actually the the gradient direction
arma::mat diagJtJ(const arma::mat &);

//This function computes the minimal vector bound
arma::vec bound_min(const int &, const arma::vec &, const std::vector<parameters> &, const double &, const double &);

//This function computes the maximal vector bound
arma::vec bound_max(const int &, const arma::vec &, const std::vector<parameters> &, const double &, const double &);

//This function computes the minimal vector bound derivative
arma::vec dbound_min(const int &, const arma::vec &, const std::vector<parameters> &, const double &, const double &);
    
//This function computes the minimal vector bound derivative
arma::vec dbound_max(const int &, const arma::vec &, const std::vector<parameters> &, const double &, const double &);
    
//This function computes the weight coefficient vector
arma::vec calcW(const int &, const int &, const arma::Col<int> &, const arma::vec &, const std::vector<arma::vec> &, const std::vector<opti_data> &, const std::vector<opti_data> &);

//This function computes the gradient of the cost function
arma::vec G_cost(const int &size, const arma::mat &S, const arma::vec &W, const arma::vec &Dv, const arma::vec &L_min, const arma::vec &L_max);
    
///Levenberg-Marquardt matrix, with bounds
arma::mat LevMarq(const arma::mat &H, const double &lambdaLM, const arma::vec &L_min, const arma::vec &L_max);
    
//This function computes the increment Dp of the parameter vector according to a Levenberg-Marquardt algorithm
arma::vec calcDp(const arma::mat &, const arma::vec &, const arma::vec &, const arma::vec &, const arma::vec &, const std::vector<parameters> &, const double &, const double &, const double &, const int &, const arma::Col<int>& );
    
} //namespace smart

