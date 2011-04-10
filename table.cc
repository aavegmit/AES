#include "table.h"
#include "word.h"
#include <stdint.h>

Table *Table::table = NULL ;

	Table *Table::Instance(){
		if (!table)
			table = new Table ;
		return table ;
	}

void Table::validateString(char *value){
	int i = 0 ; 
	while(!(value[i] == '\0' || value[i] == '\n')){
		if((value[i] < '0' || value[i] > '9') && (value[i] < 'a' || value[i] > 'f')){
			fprintf(stderr, "String not an hexadecimal value\n") ;
			exit(0) ;
		}
		++i ;
	}
}


void Table::populateS(char *value){

	if (strlen(value) != 513){
		fprintf(stderr, "%d values present in S instead of 512\n", (int)strlen(value)) ;
		exit(0) ;
	}	       

	Word w(value, 256) ;

	bool scheck[256] ;
	memset(scheck, false, 256) ;

	for (int i = 0 ; i < 256 ; i++){
		if( scheck[int(w.to_Array()[i])]){
			fprintf(stderr, "%02x value appearing twice in S\n", w.to_Array()[i]) ;
			exit(0) ;
		}
		else{
			scheck[int(w.to_Array()[i]) ] = true ;
		}
	}

	for(int i = 0 ; i < 16 ; i++){
		for(int j = 0 ; j < 16 ; j++){
			S[i][j] = w.to_Array()[i*16 + j] ;
		}
	}

	// Populate Inverse Substitution Table
	unsigned char tempc, tempres ;
	uint8_t row, col;
	for(uint8_t i = 0 ; i < 16 ; i++){
		for(uint8_t j = 0 ; j < 16 ; j++){
			tempc = S[i][j]; 
			row = tempc >> 4 ;
			col = tempc << 4 ;
			col = col >> 4 ;
			tempres = i ;
			tempres = tempres << 4 ;
			tempres = tempres | j ;
			InvS[row][col] = tempres ;
		}
	}

}

void Table::populateP(char *value){
	if (strlen(value) != 9){
		fprintf(stderr, "%d values present in P instead of 4\n", (int)strlen(value)) ;
		exit(0) ;
	}	       

	char temp1 = value[0]	 ;
	char temp2 = value[1] ;
	value[0] = value[4] ;
	value[1] = value[5] ;
	value[4] = temp1 ;
	value[5] = temp2 ;
	P = new GF28(value) ;
}


void Table::populateINVP(char *value){
	if (strlen(value) != 9){
		fprintf(stderr, "%d values present in INVP instead of 4\n", (int)strlen(value)) ;
		exit(0) ;
	}
	char temp1 = value[0]	 ;
	char temp2 = value[1] ;
	value[0] = value[4] ;
	value[1] = value[5] ;
	value[4] = temp1 ;
	value[5] = temp2 ;

	INVP = new GF28(value) ;
}



/* Loads data from the tablefile and
 * checks for the error conditions here
 */
void Table::LoadData(FILE *fp){

	char linebuf[1024] ;
	char *value ;
	int flagS = 0, flagP = 0, flagINVP = 0 ;
	while(!feof(fp)){
		memset(linebuf, '\0', 1024) ;
		fgets(linebuf, 1024, fp) ;
		if(linebuf[0] == '\0')
			break ;
		value = strchr(linebuf, '=') ;
		if (value == NULL){
			fprintf(stderr, "Invalid tablecheck file\n") ;
			exit(0) ;
		}

		*value = '\0' ;
		++value ;
		
		value[1000] = '\0' ;
		validateString(value) ;


		if (!strcmp(linebuf, "S")){
			populateS(value) ;
			flagS = 1 ;
		}
		else if(!strcmp(linebuf, "P")){
			populateP(value) ;
			flagP = 1 ;
		}
		else if(!strcmp(linebuf, "INVP")){
			populateINVP(value) ;
			flagINVP = 1 ;
		}
		else{
			fprintf(stderr, "Invalid tables file\n") ;
		}
	}
	if(!flagS){
		fprintf(stderr, "Missing S\n") ;
		exit(0) ;
	}
	if(!flagP){
		fprintf(stderr, "Missing P\n") ;
		exit(0) ;
	}
	if(!flagINVP){
		fprintf(stderr, "Missing INVP\n") ;
		exit(0) ;
	}

	// Check if polynomial represented by P and INVP is {00}{00}{00}{01}
	GF28 res((char *)("00000001")) ;
	GF28 tempg((char *)("00000000")) ;
	unsigned char tempStr1[4] ;
	P->ModProd(*INVP, tempStr1) ;
	tempg.copyW(tempStr1) ;
//	tempg.copyW( (unsigned char *)( (*P)*(*INVP)) );
	if (!( tempg == res)){
		fprintf(stderr, "Product of P and INVP is not as required\n") ;
		exit(0) ;
	}
}
