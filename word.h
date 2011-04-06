#ifndef WORD_H
#define WORD_H


#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

using namespace std ;

class Word{
	private:
		int len ;
		unsigned char *w ;
	public:
		Word(char *str, int l);			// Length of the word in bytes, default being 4
		
		Word& SubWord();			// Uses the S-box for byte-level substitution
		Word& RotWord();			// [a0, a1, a2, a3] -> [a1, a2, a3, a0]

		Word& XOR(const Word&);			// Performs the XOR function on two words
		void CircularLShift(int times=1);	// Performs Circular left shift, by default one time 
		virtual void display();			// Display the word in the required format
		unsigned char *to_Array();		// Returns the Word in array form
		bool compare(Word&);

		~Word() ;

};

#endif
