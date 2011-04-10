#ifndef BYTE_H
#define BYTE_H

#include <iostream>
#include <stdio.h>

using namespace std ;

class Byte{
	private:
		unsigned char c ;

	public:
		Byte(unsigned char) ;
		unsigned char to_uchar() ;
		Byte operator*(Byte other) ;
		Byte xtimes() ;
		Byte SubByte() ;
		Byte InvSubByte() ;
		Byte Inverse() ;
		void setC(unsigned char ch){ 
			c = ch ;
		}

};




#endif
