#include "keys.h"
#include "word.h"
#include "gf28.h"
#include "table.h"
#include "byte.h"
#include "block.h"

using namespace std ;

void EncryptOneBlock(char *input, Keys k){
	char c1[8], c2[8], c3[8], c4[8] ;
	for (int i = 0 ; i < 8 ; ++i){
		c1[i] = input[i] ;
		c2[i] = input[i+8] ;
		c3[i] = input[i+16] ;
		c4[i] = input[i+24] ;
	}

	Block in(c1, c2, c3, c4) ;
	in.Encrypt(k) ;
}


int main(int args, char **argv){

	FILE *fp ;
	fp = fopen("aes.in", "r") ;
	Table::Instance()->LoadData(fp) ;
	Word w("2b7e151628aed2a6abf7158809cf4f3c", 16) ;
	Keys k(w) ;
//	k.display() ;
	EncryptOneBlock("3243f6a8885a308d313198a2e0370734", k) ;
//	GF28 g1("d4bf5d30") ;
//	GF28 g2("01010302") ;
//	unsigned char res[4] ;
//	g1.ModProd(g2, res) ;
//	g1.copyW((unsigned char *)res);
//	g1.display() ;
//	printf("%02x\n",(Byte(0x03)*Byte(0xbf)).to_uchar()) ;


	return 0;
}
