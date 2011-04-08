#ifndef KEYS_H
#define KEYS_H

#include <iostream>
#include <stdio.h>
#include "word.h"

using namespace std ;

class Keys{
	private:
		Word *subkeys[44];
		char res[33] ;
	public:
		Keys(Word& key) ;
		void display() ;
		Word **to_Word() ;
		char *to_Array(int) ;

};

#endif
