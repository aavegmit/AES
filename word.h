#ifndef WORD_H
#define WORD_H


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "byte.h"

using namespace std ;

class Word{
	private:
		int len ;
		unsigned char *w ;
	public:
		Word(char *str, int l);			// Length of the word in bytes, default being 4
		Word(const Word& wo) ;
		
		Word SubWord();				// Uses the S-box for byte-level substitution
		void SubWord1();			// Uses the S-box for byte-level substitution
		void InvSubWord1();			// Uses the S-box for byte-level substitution
		Word RotWord();				// [a0, a1, a2, a3] -> [a1, a2, a3, a0]

		Word XOR(Word);				// Performs the XOR function on two words
		void CircularLShift(int times=1);	// Performs Circular left shift, by default one time 
		virtual void display();			// Display the word in the required format
		unsigned char *to_Array();		// Returns the Word in array form
		bool compare(Word&);
		static Word Rcon(int);
		void copyW(unsigned char *);
		Word& operator=(const Word&) ;



		void setW(int, unsigned char) ;

		void WModProd(unsigned char, char *) ;

		void Divide(Word, Word&, Word&) ;

		void Inverse() ;
		unsigned char* to_print(unsigned char *) ;

		~Word() ;

};

#endif
