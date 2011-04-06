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



	return 0;
}
