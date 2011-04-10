#include "byte.h"
#include "table.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

Byte::Byte(unsigned char ch){
	c = ch ;
}

unsigned char Byte::to_uchar(){
	return c;
}

// The very important xtimes operation
Byte Byte::xtimes(){
	unsigned char temp = c, temp1 = c;
	temp1 = temp1 << 1 ;
	temp = temp >> 7;
	// Needs to be XOR with {1B}
	if(temp){
		temp1 = temp1^(0x1b) ;
	}
	return Byte(temp1) ;
}

// The big DOT operation
Byte Byte::operator*(Byte other){
	Byte *v[8] ;
	v[0] = new Byte(0x00) ;
	v[0] = this ;
	for(int i = 1 ; i < 8 ; ++i){
		v[i] = new Byte(0x00) ;
		*v[i] = v[i-1]->xtimes() ;
	}
	unsigned char temp = 0x00 ;
	int i = 0 ;
	for(unsigned char t = 0x01; t != 0x00 ; t <<= 1){
		if(t & other.to_uchar())
			temp = temp ^ v[i]->to_uchar() ;
		++i ;
	}
	return Byte(temp) ;

}

// Substitution using S-Box at the byte level
Byte Byte::SubByte(){
	uint8_t row = 0, col = 0 ;
	row = c >> 4 ;
	col = (c << 4)   ;
	col = col >> 4 ;
	unsigned char c1 = Table::Instance()->S[row][col] ;
	return Byte(c1) ;
}


Byte Byte::InvSubByte(){
	uint8_t row = 0, col = 0 ;
	row = c >> 4 ;
	col = (c << 4)   ;
	col = col >> 4 ;
	unsigned char c1 = Table::Instance()->InvS[row][col] ;
	return Byte(c1) ;
}

// Find the inverse of the byte, using the brute force method
Byte Byte::Inverse(){
	if (c == 0x00)
		return Byte(0x00) ;
	if (c == 0x1c)
		return Byte(0xff) ;
	for(uint8_t i = 0x01 ; i <= 0xfe; ++i){
		if(((*this)*Byte((unsigned char) (i))).to_uchar() == 0x01)
			return Byte( (unsigned char)i) ;
	}
	return Byte(0x00) ;
}
