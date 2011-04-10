#ifndef GF28_H
#define GF28_H

#include <stdio.h>
#include <iostream>
#include "word.h"
#include "byte.h"

using namespace std ;

class GF28: public Word{
	private:
		char d[4] ;

	public:
		GF28(char *str) : Word(str, 4){} ;	// Constructor method
		GF28();

		void display() ;			// Method to display the coefficients in required format
//		char *operator*(GF28 &other);		// Operator overloading so as to perform mod product of two
							// GF28 polynomials
		void ModProd(GF28 &other,unsigned char *);
		bool operator==(GF28 &other);		// To compare two GF(2^8) polynomials
		GF28 operator=(GF28);
		GF28& Inverse();			// To compute the multiplicative inverse of the given polynomia
		~GF28() ;

};

#endif
