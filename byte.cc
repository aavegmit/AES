#include "byte.h"

Byte::Byte(unsigned char ch){
	c = ch ;
}

unsigned char Byte::to_uchar(){
	return c;
}

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
