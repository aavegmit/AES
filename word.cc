#include "word.h"
#include "gf28.h"

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


void Word::copyW(unsigned char *w1){
	for(int i = 0 ; i < len ; ++i)
		w[i] = w1[i] ;
}

void Word::setW(int index ,unsigned char w1 ){
	w[index] = w1 ;
}

// Copy constructor
Word::Word(const Word& wo){
	len = wo.len ;
	w = new unsigned char[len] ;
	for(int i = 0 ; i < len ; ++i)
		w[i] = wo.w[i] ;
}

// Assignment operator overloading
Word& Word::operator=(const Word& wo){
	w = new unsigned char[len] ;
	for(int i = 0 ; i < len ; ++i)
		w[i] = wo.w[i] ;
	return *this ;
}

// Substitution using S-Box
Word Word::SubWord(){
	char temp[len*2] ;
	for(int i = 0 ; i < len ; ++i){
		Byte b(w[i]) ;
		sprintf(&temp[i*2],"%02x", b.SubByte().to_uchar()) ;
	}
	return Word(temp,len) ;
}


void Word::SubWord1(){
	char temp[len*2] ;
	for(int i = 0 ; i < len ; ++i){
		Byte b(w[i]) ;
		sprintf(&temp[i*2],"%02x", b.SubByte().to_uchar()) ;
	}
	*this = Word(temp,len) ;
}

void Word::InvSubWord1(){
	char temp[len*2] ;
	for(int i = 0 ; i < len ; ++i){
		Byte b(w[i]) ;
		sprintf(&temp[i*2],"%02x", b.InvSubByte().to_uchar()) ;
	}
	*this = Word(temp,len) ;
}

// Performs the ROTWORD operation
Word Word::RotWord(){
	if(len == 4){
		char temp[8] ;
		sprintf(temp,"%02x%02x%02x%02x", w[1], w[2],w[3],w[0]) ;
		return Word(temp,4) ;
	}
	else
		return Word((char *)("00000000")) ;
}

// Used for Addiotion or Substraction
Word Word::XOR(Word wo){
	char *temp = new char[len*2] ;
	for(int i = 0 ; i < wo.len ; ++i){
		sprintf(&temp[i*2],"%02x", w[i]^wo.w[i]) ;
	}
	for(int i = wo.len ; i < len ; ++i){
		sprintf(&temp[i*2],"%02x", w[i]) ;
	}

	return Word(temp, len) ;
}

// for debugging purposes only
void Word::display(){
	for(int i = 0 ; i < len ; i++){
		printf("%02x", w[i]) ;
	}
	printf("\n") ;
}


unsigned char *Word::to_Array(){
	return w;
}


// The Rcon constant
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

void Word::WModProd(unsigned char ch, char *res){

	Byte b1(ch) ;

	for (int i = 0 ; i < len ; ++i){
		sprintf(&res[i*2], "%02x", (b1*Byte(w[i])).to_uchar()) ;
	}
}

void Word::Inverse(){

	Word Q((char *)("00000000"), 4) ;
	Word D((char *)("0100000001"), 5) ;

	Word *rem[7], *quo[7], *aux[7] ;
	rem[1] = new Word((char *)("0100000001"),5) ;
	rem[2] = new Word(*this) ;
	quo[1] = new Word((char *)("00000000") ,4) ;
	quo[2] = new Word((char *)("00000000") ,4) ;
	aux[1] = new Word((char *)("00000000") ,4) ;
	aux[2] = new Word((char *)("00000001") ,4) ;

	unsigned char str[17] ;

	printf("i=1, rem[i]={00}{00}{00}{01}, quo[i]={00}{00}{00}{00}, aux[i]={00}{00}{00}{00}\n") ;

	rem[2]->to_print(str) ;
	printf("i=2, rem[i]=%s, ", str ) ;
	quo[2]->to_print(str) ;
	printf("quo[i]=%s, ", str) ;
	aux[2]->to_print(str) ;
	printf("aux[i]=%s\n", str ) ;

	int flag = 0 ;
	for (int h = 0 ; h < rem[2]->len ; ++h){
		if (rem[2]->to_Array()[h] != 0x00){
			flag = 1 ;
			break ;
		}
	}

	if (!flag){
		printf("Multiplicative inverse of {00}{00}{00}{00} is {00}{00}{00}{00}\n") ;
		return ;
	}
	GF28 temp1((char *)("00000000")) ;
	GF28 temp2((char *)("00000000")) ;
	Word zeroWord((char *)("00000000"), 4) ;
	for(int i = 3 ; i < 7 ; ++i){
		if ( i == 6 ){
			rem[i-2]->w[ rem[i-2]->len -1  ] = rem[i-2]->w[ rem[i-2]->len - 1  ] ^ 0x01 ;
			//			printf("final round: %02x\n", rem[4]->to_Array()[rem[4]->len - 1]) ;
		}
		Word temp(*rem[i-2]) ;
		Word Q((char *)("00000000"), 4) ;
		temp.Divide(*rem[i-1], Q, temp) ;
		rem[i] = new Word(temp) ;
		aux[i] = new Word((char *)("00000000"), 4) ;
		unsigned char tempStr[4] ;
		temp1.copyW(Q.to_Array()) ;
		temp2.copyW(aux[i-1]->to_Array()) ;
		temp1.ModProd(temp2, tempStr) ;
		quo[i] = new Word((char *)("00000000"), 4) ;
		quo[i]->copyW(Q.to_Array()) ;
		aux[i]->copyW(tempStr) ;
		*aux[i] = aux[i]->XOR(*aux[i-2]) ;

		if (i==6){
			rem[i]->w[rem[i]->len - 1] = 0x01 ;
		}
		rem[i]->to_print(str) ;
		printf("i=%d, rem[i]=%s, ",i, str ) ;
		quo[i]->to_print(str) ;
		printf("quo[i]=%s, ", str) ;
		aux[i]->to_print(str) ;
		printf("aux[i]=%s\n", str ) ;

		int flag = 0 ;
		for (int h = 0 ; h < D.len ; ++h){
			if (rem[i]->to_Array()[h] != 0x00){
				flag = 1 ;
				break ;
			}
		}

		if (!flag){
			rem[2]->to_print(str) ;
			printf("%s does not have a multiplicative inverse.\n", str) ;
			return ;
		}
	}


	rem[2]->to_print(str) ;
	printf("Multiplicative inverse of %s is ", str) ;
	aux[6]->to_print(str) ;
	printf("%s\n", str) ;	


	//	Divide(*this, Q, D) ;

}


unsigned char *Word::to_print(unsigned char *str){
	for(int i = 0 ; i < (4 - len) ; ++i){
		sprintf((char *)&str[i*4], "{00}") ;
	}
	for(int i = (4 - len) ; i < 4 ; ++i){
		sprintf((char *)&str[i*4], "{%02x}", w[i-4+len] ) ;
	}
	str[16] = '\0' ;
	return str ;
}

void Word::Divide(Word wo, Word& Q, Word& D){
	if (len < wo.len){
		fprintf(stderr, "Error in division\n");
		exit(0) ;
	}

	//	Word Q("00000000", 4) ;
	//	Word D(*this) ;

	Byte b3(wo.to_Array()[0]) ;
	for (int h = 0 ; h < wo.len ; ++h){
		if (wo.to_Array()[h] != 0x00){
			b3.setC( wo.to_Array()[h])  ;
			for (int j = 0 ; j < wo.len - h ; ++j)
				wo.w[j] = wo.w[j+h] ;
			wo.len = wo.len - h ;
			break ;
		}

	}

	int ctr = 0 ;
	for (int i = 0 ; i < 1 ; ++i){
		Q = Q.RotWord() ;
		Q.setW(3, (b3.Inverse()*Byte(D.w[0])).to_uchar()) ;

		char tempStr[9] ;
		wo.WModProd( Q.w[3] , tempStr) ;

		Word temp1((char *)tempStr, wo.len) ;
		D = D.XOR(temp1) ;

		int flag = 0 ;
		for (int h = 0 ; h < D.len ; ++h){
			if (D.to_Array()[h] != 0x00){
				for (int j = 0 ; j < D.len - h ; ++j)
					D.w[j] = D.w[j+h] ;
				D.len = D.len - h ;
				flag = 1 ;
				break ;
			}

		}
		if(!flag)
			break ;


		if(D.len >= wo.len){
			//			for (int j = 0 ; j < 4 ; ++j)
			//				D.w[j] = D.w[j+1] ;
			//			D.len = wo.len ;
			--i ;
		}

		++ctr ;
		if (ctr >= 10){
			break ;
		}
	}
	//	Q.display() ;
	//	D.display() ;

}


// Destructor definition for the class Word
Word::~Word(){
	delete []w ;
}
