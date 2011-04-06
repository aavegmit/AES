#ifndef KEYS_H
#define KEYS_H

#include <iostream>
#include <stdio.h>
#include "word.h"

using namespace std ;

class Keys{
	private:
		Word *subkeys[44];
	public:
		Keys(Word& key) ;

};

#endif
