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

///@file generation.hpp
///@brief generation for genetic algorithm (among others)
///@author Chemisky & Despringre
///@version 1.0

#pragma once
#include <iostream>
#include <armadillo>
#include "individual.hpp"

namespace smart{

//======================================
class generation
//======================================
{
	private:

	protected:

	public :
		int nindividuals;
		
        std::vector<individual> pop;
		
		generation(); 	//default constructor
		generation(int, int, int&);	//constructor - allocates memory for statev
		generation(const generation&);	//Copy constructor
		~generation();
		
		int dimindividuals() const {return nindividuals;}       // returns the number of individuals

		void construct(const int&, int&);
		void classify();
		void newid(int &);
		void destruct();

		virtual generation& operator = (const generation&);
		
		friend std::ostream& operator << (std::ostream&, const generation&);
};

} //namespace smart
