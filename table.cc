#include "table.h"
#include "word.h"

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

}

void Table::populateP(char *value){
	if (strlen(value) != 9){
		fprintf(stderr, "%d values present in P instead of 4\n", (int)strlen(value)) ;
		exit(0) ;
	}	       

	P = new GF28(value) ;
}


void Table::populateINVP(char *value){
	if (strlen(value) != 9){
		fprintf(stderr, "%d values present in INVP instead of 4\n", (int)strlen(value)) ;
		exit(0) ;
	}	       

	INVP = new GF28(value) ;
}



/* Loads data from the tablefile and
 * checks for the error conditions here
 */
void Table::LoadData(FILE *fp){

	char linebuf[1024] ;
	char *value ;
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
		}
		else if(!strcmp(linebuf, "P")){
			populateP(value) ;
		}
		else if(!strcmp(linebuf, "INVP")){
			populateINVP(value) ;
		}
		else{
			fprintf(stderr, "Invalid tables file\n") ;
		}
	}

	// Check if polynomial represented by P and INVP is {00}{00}{00}{01}
	GF28 res("00000001") ;
	GF28 tempg("00000000") ;
	tempg.copyW( (unsigned char *)( (*P)*(*INVP)) );
	if (!( tempg == res)){
		fprintf(stderr, "Product of P and INVP is not as required\n") ;
		exit(0) ;
	}
}
