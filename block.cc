#include "block.h"

// Cosntructor definition
Block::Block(char *c1, char *c2,char *c3,char *c4){
	g[0] = new GF28(c1) ;
	g[1] = new GF28(c2) ;
	g[2] = new GF28(c3) ;
	g[3] = new GF28(c4) ;
	return ;
}

// Performs substituion using the S-Box
void Block::SubBytes(){
	for(int i = 0 ; i < 4 ; ++i){
		g[i]->SubWord1() ;
	}
}

// Performs the shift row operation
void Block::ShiftRows(){
	for (int i = 1; i < 4 ; ++i){
		for(int j = 0 ; j < i ; ++j)
			ShiftRowOnce(i) ;
	}
}

// Shifts the row just once
void Block::ShiftRowOnce(int row){
	unsigned char temp = g[0]->to_Array()[row] ;
	for(int i = 0 ; i < 3; ++i)
		g[i]->to_Array()[row] = g[i+1]->to_Array()[row] ;
	g[3]->to_Array()[row] = temp ;
}

// Performs the mix col operation
void Block::MixColumns(){
//	GF28 temp(const_cast<char *>(string("01010302").c_str())) ;
	GF28 temp((char *)("00000000")) ;
	temp = *(Table::Instance()->P) ;
	unsigned char res[4] ;
	for(int i=0; i < 4; ++i){
		temp.ModProd(*g[i], res) ;
		g[i]->copyW((unsigned char *)res) ;
	}
//		g[i]->copyW((unsigned char*)((*g[i])*temp)  ) ;
//		((*g[i])*temp).display() ;
//		*g[i] = (*g[i])*temp ;
}

void Block::InvSubBytes(){
	for(int i = 0 ; i < 4 ; ++i){
		g[i]->InvSubWord1() ;
	}
}

void Block::InvShiftRows(){
	for (int i = 1; i < 4 ; ++i){
		for(int j = 0 ; j < i ; ++j)
			InvShiftRowOnce(i) ;
	}
}

void Block::InvShiftRowOnce(int row){
	unsigned char temp = g[3]->to_Array()[row] ;
	for(int i = 3 ; i > 0; --i)
		g[i]->to_Array()[row] = g[i-1]->to_Array()[row] ;
	g[0]->to_Array()[row] = temp ;
}

void Block::InvMixColumns(){
//	GF28 temp(const_cast<char *>(string("090d0b0e").c_str())) ;
	GF28 temp((char *)("00000000")) ;
	temp = *(Table::Instance()->INVP) ;
	unsigned char res[4] ;
	for(int i=0; i < 4; ++i){
		temp.ModProd(*g[i], res) ;
		g[i]->copyW((unsigned char *)res) ;
	}
//		g[i]->copyW((unsigned char*)((*g[i])*temp)  ) ;
//		((*g[i])*temp).display() ;
//		*g[i] = (*g[i])*temp ;
}


void Block::AddRoundKey(Keys &k, int round){
	unsigned char newW[4] ;
	for(int i=0; i < 4 ; ++i){
		for(int j = 0 ; j < 4 ; ++j){
			newW[j] = g[i]->to_Array()[j] ^ k.to_Word()[round*4+i]->to_Array()[j] ;
		}
		g[i]->copyW(newW) ;
//		*(dynamic_cast<GF28 *>(g[i])) = *(dynamic_cast<GF28 *>(&(g[i]->XOR(*(k.to_Word()[round*4+i]))))) ;
	}
}

void Block::Encrypt(Keys &k){
	printf("round[ 0].input    %s\n", to_Array()) ;
	AddRoundKey(k, 0) ;
	printf("round[ 0].k_sch    %s\n", k.to_Array(0)) ;

	for(int round = 1 ; round < 10 ; ++round){
		printf("round[ %d].start    %s\n",round,  to_Array()) ;
		SubBytes() ;
		printf("round[ %d].s_box    %s\n",round,  to_Array()) ;
		ShiftRows() ;
		printf("round[ %d].s_row    %s\n",round,  to_Array()) ;
		MixColumns() ;
		printf("round[ %d].m_col    %s\n",round,  to_Array()) ;
		AddRoundKey(k, round) ;
		printf("round[ %d].k_sch    %s\n",round,  k.to_Array(round)) ;
	}

	int round = 10 ;
	printf("round[%d].start    %s\n",round,  to_Array()) ;
	SubBytes();
	printf("round[%d].s_box    %s\n",round,  to_Array()) ;
	ShiftRows();
	printf("round[%d].s_row    %s\n",round,  to_Array()) ;
	AddRoundKey(k, 10);
	printf("round[%d].k_sch    %s\n",round,  k.to_Array(round)) ;
	printf("round[%d].output   %s\n",round,  to_Array()) ;

}

void Block::Decrypt(Keys &k){
	printf("round[ 0].iinput   %s\n", to_Array()) ;
	AddRoundKey(k, 10) ;
	printf("round[ 0].ik_sch   %s\n", k.to_Array(10)) ;

	for(int round = 9 ; round > 0 ; --round){
		printf("round[ %d].istart   %s\n",10-round,  to_Array()) ;

		InvShiftRows() ;
		printf("round[ %d].is_row   %s\n",10-round,  to_Array()) ;

		InvSubBytes() ;
		printf("round[ %d].is_box   %s\n",10-round,  to_Array()) ;

		AddRoundKey(k, round) ;
		printf("round[ %d].ik_sch   %s\n",10-round,  k.to_Array(round)) ;
		printf("round[ %d].ik_add   %s\n",10-round,  to_Array()) ;
		
		InvMixColumns() ;
//		printf("round[ %d].im_col:   %s\n",10-round,  to_Array()) ;

	}

	int round = 0 ;
	printf("round[%d].istart   %s\n",10-round,  to_Array()) ;
	InvShiftRows();
	printf("round[%d].is_row   %s\n",10-round,  to_Array()) ;
	InvSubBytes();
	printf("round[%d].is_box   %s\n",10-round,  to_Array()) ;
	AddRoundKey(k, 0);
	printf("round[%d].ik_sch   %s\n",10-round,  k.to_Array(round)) ;
	printf("round[%d].ioutput  %s\n",10-round,  to_Array()) ;

}


char *Block::to_Array(){
	for(int i = 0 ; i < 4 ; ++i){
		for(int j = 0 ; j < 4 ; ++j){
			sprintf(&res[i*8+j*2], "%02x", g[i]->to_Array()[j]) ;
		}
	}
	res[32] = '\0' ;
	return res ;
}

Block::~Block(){
//	delete g;
}
