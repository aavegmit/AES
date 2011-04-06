#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gf28.h"
#include "word.h"

using namespace std ;


// Table class to check and hold data from the
// tablefile. Design based on SINGLETON class
// as we want only one of its object to be created
// and globally available to all other parts of the 
// code.
class Table{
	private:
		Table(){} ;				// Private so that it could not be called
		Table(Table const&){};			// Copy constructor is also made private
		Table& operator=(Table const&);		// assignment operator is private
		static Table* table;			// Unique instance that is available in all
							// parts of the code

	public:
		static Table* Instance() ;		// Returns the unique instance of this class
		unsigned char S[16][16] ;
		GF28 *P ;
		GF28 *INVP;

		void LoadData(FILE *fp) ;		// Load data from the tablefile
		void populateS(char *);
		void populateP(char *);
		void populateINVP(char *);
		void validateString(char *);

};

#endif
