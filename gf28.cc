#include "gf28.h"


char *GF28::operator*(GF28 &other){
	char d[4] ;
	d[3] = (Byte(to_Array()[3]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[0])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[1])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[2])*Byte(other.to_Array()[0])).to_uchar() ;

	d[2] = (Byte(to_Array()[2]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[3])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[0])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[1])*Byte(other.to_Array()[0])).to_uchar() ;

	d[1] = (Byte(to_Array()[1]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[2])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[3])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[0])*Byte(other.to_Array()[0])).to_uchar() ;

	d[0] = (Byte(to_Array()[0]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[1])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[2])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[3])*Byte(other.to_Array()[0])).to_uchar() ;


	char tempstr[9] ;
	sprintf(tempstr, "%02x%02x%02x%02x", d[0], d[1], d[2], d[3]) ;
//	GF28 g(tempstr) ;
//	return g;
	return d;
}

void GF28::ModProd(GF28 &other, unsigned char *d){
	d[3] = (Byte(to_Array()[3]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[0])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[1])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[2])*Byte(other.to_Array()[0])).to_uchar() ;

	d[2] = (Byte(to_Array()[2]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[3])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[0])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[1])*Byte(other.to_Array()[0])).to_uchar() ;

	d[1] = (Byte(to_Array()[1]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[2])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[3])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[0])*Byte(other.to_Array()[0])).to_uchar() ;

	d[0] = (Byte(to_Array()[0]) * Byte(other.to_Array()[3])).to_uchar() ^  
		(Byte(to_Array()[1])*Byte(other.to_Array()[2])).to_uchar() ^
		(Byte(to_Array()[2])*Byte(other.to_Array()[1])).to_uchar() ^
		(Byte(to_Array()[3])*Byte(other.to_Array()[0])).to_uchar() ;


//	char tempstr[9] ;
//	sprintf(tempstr, "%02x%02x%02x%02x", d[0], d[1], d[2], d[3]) ;
//	GF28 g(tempstr) ;
//	return g;
//	return d;

}


GF28 GF28::operator=(GF28 gf){
	copyW(gf.to_Array()) ;
	return *this ;
}

bool GF28::operator==(GF28 &other){
	return compare(dynamic_cast<Word &>(other)) ;
}


void GF28::display(){
	for (int i = 0 ; i < 4 ; ++i)
		printf("{%02x}", to_Array()[i]) ;
	printf("\n") ;
}

GF28::~GF28(){
}
