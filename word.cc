#include "word.h"


// Constructor definition for the class Word
Word::Word(char *str, int l=4){
	len = l ;
	w = new unsigned char[len] ;

	memset(w, 0, len) ;

	for(int i=0 ; i < l ; i++){
		if(str[i*2] >= '0' && str[i*2] <= '9'  ) {
			w[i] = str[i*2] - 48 ;
		}
		else if(str[i*2] >= 'a' && str[i*2] <= 'f'  ) {
			w[i] = str[i*2] - 87 ;
		}
		else{
			fprintf(stderr, "Value not a hexstring\n") ;
			exit(0) ;
		}

		w[i] = w[i] << 4 ;

		if(str[i*2+1] >= '0' && str[i*2+1] <= '9'  ) {
			w[i] = w[i] | (str[i*2+1] - 48) ;
		}
		else if(str[i*2+1] >= 'a' && str[i*2+1] <= 'f'  ) {
			w[i] = w[i] | (str[i*2+1] - 87) ;
		}
		else{
			fprintf(stderr, "Value not a hexstring\n") ;
			exit(0) ;
		}

	}

}


Word& Word::SubWord(){
}


Word& Word::RotWord(){
}


Word& Word::XOR(const Word& w){
}

void Word::display(){
	for(int i = 0 ; i < len ; i++){
		printf("%02x", w[i]) ;
	}
	printf("\n") ;
}


unsigned char *Word::to_Array(){
	return w;
}


bool Word::compare(Word& other){
	if (len != other.len)
		return false ;
	for (int i =0 ; i < len ; i++){
		if (w[i] != other.to_Array()[i])
			return false ;
	}
	return true ;
}

// Destructor definition for the class Word
Word::~Word(){
	delete w ;
}
