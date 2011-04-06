#ifndef GF28_H
#define GF28_H

#include <stdio.h>
#include <iostream>
#include "word.h"
#include "byte.h"

using namespace std ;

class GF28: public Word{

	public:
		GF28(char *str) : Word(str, 4){} ;	// Constructor method

		void display() ;			// Method to display the coefficients in required format
		GF28 operator*(GF28 &other);		// Operator overloading so as to perform mod product of two
							// GF28 polynomials
		bool operator==(GF28 &other);		// To compare two GF(2^8) polynomials
		GF28& Inverse();			// To compute the multiplicative inverse of the given polynomia

};

#endif
