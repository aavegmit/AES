#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <stdio.h>
#include "gf28.h"
#include "keys.h"
#include "table.h"

using namespace std ;

class Block{
	private:
		GF28 *g[4] ;
		char res[33] ;
	public:
//		Block(GF28& ,GF28& ,GF28& ,GF28& ) ;		// Constructor method
		Block(char * ,char * ,char * ,char * ) ;		// Constructor method
		Block();
		void SubBytes();
		void ShiftRows();				// Shift Rows operation
		void ShiftRowOnce(int row) ;			// Shift Row once
		void MixColumns();
		void AddRoundKey(Keys&,int);			// Bit wise XOR with the round key

		void Encrypt(Keys&) ;
		void Decrypt(Keys&) ;
		char *to_Array();

		void InvSubBytes();
		void InvShiftRows();				// Shift Rows operation
		void InvShiftRowOnce(int row) ;			// Shift Row once
		void InvMixColumns();

		~Block() ;					// Destructor Method

};

#endif
