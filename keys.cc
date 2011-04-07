#include "keys.h"

Keys::Keys(Word& key){
	char tempStr[8] ;

	for (int i=0; i < 4; i++) {
		sprintf(tempStr, "%02x%02x%02x%02x", key.to_Array()[4*i], key.to_Array()[4*i+1], key.to_Array()[4*i+2], key.to_Array()[4*i+3]) ;
		subkeys[i] = new Word(tempStr, 4) ;
	}

	Word temp(*(subkeys[3])) ;
	for (int i=4 ; i < 44; ++i){
		temp = *(subkeys[i-1]) ;

		if ( i%4 == 0){
			temp = (((temp.RotWord()).SubWord()).XOR(Word::Rcon(i/4))) ; 
		}
		subkeys[i] = new Word(subkeys[i-4]->XOR(temp)) ;
	}


}

void Keys::display(){
	for(int i = 0 ; i < 10 ; ++i){
		printf("w[ %d]: %02x%02x%02x%02x\n",i,subkeys[i]->to_Array()[0],subkeys[i]->to_Array()[1] ,subkeys[i]->to_Array()[2] ,subkeys[i]->to_Array()[3] ) ;
	}
	for(int i = 10 ; i < 44 ; ++i){
		printf("w[%d]: %02x%02x%02x%02x\n",i,subkeys[i]->to_Array()[0],subkeys[i]->to_Array()[1] ,subkeys[i]->to_Array()[2] ,subkeys[i]->to_Array()[3] ) ;
	}

}
