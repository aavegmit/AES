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

Word::Word(const Word& wo){
	len = wo.len ;
	w = new unsigned char[len] ;
	for(int i = 0 ; i < len ; ++i)
		w[i] = wo.w[i] ;
}

Word& Word::operator=(const Word& wo){
	w = new unsigned char[len] ;
	for(int i = 0 ; i < len ; ++i)
		w[i] = wo.w[i] ;
	return *this ;
}

Word Word::SubWord(){
	char temp[len*2] ;
	for(int i = 0 ; i < len ; ++i){
		Byte b(w[i]) ;
		sprintf(&temp[i*2],"%02x", b.SubByte().to_uchar()) ;
	}
	return Word(temp,len) ;
}


Word Word::RotWord(){
	if(len == 4){
		char temp[8] ;
		sprintf(temp,"%02x%02x%02x%02x", w[1], w[2],w[3],w[0]) ;
		return Word(temp) ;
	}
	else
		return Word("00000000") ;
}


Word Word::XOR(Word wo){
	char *temp = new char[len*2] ;
	for(int i = 0 ; i < len ; ++i){
		sprintf(&temp[i*2],"%02x", w[i]^wo.w[i]) ;
	}
	return Word(temp, len) ;
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


Word Word::Rcon(int i){
	Byte b(0x02), tem(0x01) ;
	for(int j = 1 ; j < i ; ++j){
		tem = tem*b ;
	}
	char temp[8] ;
	sprintf(temp, "%02x", tem.to_uchar()) ;
	memset(&temp[2], '0', 6) ;
	return Word(temp) ;
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
