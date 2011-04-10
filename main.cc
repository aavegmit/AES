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


void DecryptOneBlock(char *input, Keys k){
	char c1[8], c2[8], c3[8], c4[8] ;
	for (int i = 0 ; i < 8 ; ++i){
		c1[i] = input[i] ;
		c2[i] = input[i+8] ;
		c3[i] = input[i+16] ;
		c4[i] = input[i+24] ;
	}

	Block in(c1, c2, c3, c4) ;
	in.Decrypt(k) ;
}


int main(int args, char **argv){

	FILE *fp ;
	fp = fopen("aes.in", "r") ;
	Table::Instance()->LoadData(fp) ;
	Word w("000102030405060708090a0b0c0d0e0f", 16) ;
	Keys k(w) ;
//	k.display() ;
//	EncryptOneBlock("3243f6a8885a308d313198a2e0370734", k) ;
//	DecryptOneBlock("69c4e0d86a7b0430d8cdb78070b4c55a", k) ;
//	GF28 g1("d4bf5d30") ;
//	GF28 g2("01010302") ;
//	unsigned char res[4] ;
//	g1.ModProd(g2, res) ;
//	g1.copyW((unsigned char *)res);
//	g1.display() ;
//	printf("%02x\n",(Byte(0x0e)*Byte(0xe9)).to_uchar()) ;
//	printf("%02x\n",(Byte(0x0b)*Byte(0xf7)).to_uchar()) ;
//	printf("%02x\n",(Byte(0x0d)*Byte(0x4e)).to_uchar()) ;
//	printf("%02x\n",(Byte(0x09)*Byte(0xec)).to_uchar()) ;
//	printf("%02x\n",Byte(0x00).Inverse().to_uchar()) ;
//	printf("%02x\n",Byte(0xff).Inverse().to_uchar()) ;
	Word w1("01020102",4) ;
	Word w2("9ad1",2) ;
	w1.Inverse() ;


	return 0;
}
