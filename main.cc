#include "keys.h"
#include "word.h"
#include "gf28.h"
#include "table.h"
#include "byte.h"

using namespace std ;

int main(int args, char **argv){

	FILE *fp ;
	fp = fopen("aes.in", "r") ;
	Table::Instance()->LoadData(fp) ;
	Word w("2b7e151628aed2a6abf7158809cf4f3c", 16) ;
	Keys k(w) ;
	k.display() ;



	return 0;
}
