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

// Usage of the program
void usage(){
	printf("Usage:\n\t ./hw6 tablecheck -t=tablefile\n") ;
	printf("\t ./hw6 modprod -p1=poly1 -p2=poly2\n") ;
	printf("\t ./hw6 keyexpand -k=key -t=tablefile\n") ;
	printf("\t ./hw6 encrypt -k=key -t=tablefile [file]\n") ;
	printf("\t ./hw6 decrypt -k=key -t=tablefile [file]\n") ;
	printf("\t ./hw6 inverse -p=poly\n") ;
	exit(0) ;
}

int main(int argc, char **argv){

	int choice;
	char *poly1, *poly2, *key, *tablefile ;
	FILE *inpF ;


	// Parse the command line 
	if (argc < 3){
		usage() ;
	}
	else {
		argv++ ;
		if (strcmp(*argv, "tablecheck") == 0) {
			choice = 1 ;
		} else if (strcmp(*argv, "modprod") == 0) {
			choice = 2 ;
		} else if (strcmp(*argv, "keyexpand") == 0) {
			choice = 3 ;
		} else if (strcmp(*argv, "encrypt") == 0) {
			choice = 4 ;
		} else if (strcmp(*argv, "decrypt") == 0) {
			choice = 5 ;
		} else if (strcmp(*argv, "inverse") == 0) {
			choice = 6 ;
		} else {
			usage() ;
		}

		argv++ ;

		// keygen chosen
		if (choice == 1){
			if (argc < 3){
				usage() ;
			}
			for (int i = 0 ; i < 1 ; i++, argv++) {
				if (*argv[0] == '-') {
					if (argv[0][1] == 't') {
						/* read pphrase from *argv */
						tablefile = strtok(*argv, "=") ;
						tablefile = strtok(NULL, "=") ;
						if (tablefile == NULL)
							usage() ;
					} 
					else{
						usage() ;
					}
				}
				else{
					usage() ;	
				}

			}
		}
		else if (choice == 6){
			if (argc < 3){
				usage() ;
			}
			for (int i = 0 ; i < 1 ; i++, argv++) {
				if (*argv[0] == '-') {
					if (argv[0][1] == 'p') {
						/* read pphrase from *argv */
						poly1 = strtok(*argv, "=") ;
						poly1 = strtok(NULL, "=") ;
						if (poly1 == NULL)
							usage() ;
					} 
					else{
						usage() ;
					}
				}
				else{
					usage() ;	
				}

			}
		}
		else if(choice == 2){
			if (argc < 4){
				usage() ;
			}
			for (int i = 0 ; i < 2 ; i++, argv++) {
				if (*argv[0] == '-') {
					if (argv[0][1] == 'p' && argv[0][2] == '1') {
						/* read pphrase from *argv */
						poly1 = strtok(*argv, "=") ;
						poly1 = strtok(NULL, "=") ;
						if (poly1 == NULL)
							usage() ;
					} 
					else if (argv[0][1] == 'p' && argv[0][2] == '2' ) {
						/* read pphrase from *argv */
						poly2 = strtok(*argv, "=") ;
						poly2 = strtok(NULL, "=") ;
						if (poly2 == NULL)
							usage() ;
					} 
					else{
						usage() ;
					}
				}
				else{
					usage() ;	
				}

			}
			//			if (argc == 5){
			//				inpF = fopen(*argv, "r") ;
			//			       if (inpF == NULL){
			//				       fprintf(stderr, "File could not be opened\n") ;
			//				       exit(0) ;
			//			       }	       
			//			}
			//			else{
			//				inpF = stdin ;
			//			}
		}
		// Invkey command line option
		else if(choice == 3){
			if (argc < 4){
				usage() ;
			}
			for (int i = 0 ; i < 2 ; i++, argv++) {
				if (*argv[0] == '-') {
					if (argv[0][1] == 'k') {
						/* read pphrase from *argv */
						key = strtok(*argv, "=") ;
						key = strtok(NULL, "=") ;
						if (key == NULL)
							usage() ;
					} 
					else if (argv[0][1] == 't') {
						/* read pphrase from *argv */
						tablefile = strtok(*argv, "=") ;
						tablefile = strtok(NULL, "=") ;
						if (tablefile == NULL)
							usage() ;
					} 
					else{
						usage() ;
					}
				}
				else{
					usage() ;	
				}

			}
			//			if (argc == 5){
			//				inpF = fopen(*argv, "r") ;
			//			       if (inpF == NULL){
			//				       fprintf(stderr, "File could not be opened\n") ;
			//				       exit(0) ;
			//			       }	       
			//			}
			//			else{
			//				inpF = stdin ;
			//			}
		}
		// Histo command line option
		else if(choice == 4){
			if (argc < 4){
				usage() ;
			}
			for (int i = 0 ; i < 2 ; i++, argv++) {
				if (*argv[0] == '-') {
					if (argv[0][1] == 'k') {
						/* read pphrase from *argv */
						key = strtok(*argv, "=") ;
						key = strtok(NULL, "=") ;
						if (key == NULL)
							usage() ;
					} 
					else if (argv[0][1] == 't') {
						/* read pphrase from *argv */
						tablefile = strtok(*argv, "=") ;
						tablefile = strtok(NULL, "=") ;
						if (tablefile == NULL)
							usage() ;
					} 
					else{
						usage() ;
					}
				}
				else{
					usage() ;	
				}

			}
			if (argc == 5){
				inpF = fopen(*argv, "r") ;
				if (inpF == NULL){
					fprintf(stderr, "File could not be opened\n") ;
					exit(0) ;
				}	       
			}
			else{
				inpF = stdin ;
			}
		}
		else if(choice == 5){
			if (argc < 4){
				usage() ;
			}
			for (int i = 0 ; i < 2 ; i++, argv++) {
				if (*argv[0] == '-') {
					if (argv[0][1] == 'k') {
						/* read pphrase from *argv */
						key = strtok(*argv, "=") ;
						key = strtok(NULL, "=") ;
						if (key == NULL)
							usage() ;
					} 
					else if (argv[0][1] == 't') {
						/* read pphrase from *argv */
						tablefile = strtok(*argv, "=") ;
						tablefile = strtok(NULL, "=") ;
						if (tablefile == NULL)
							usage() ;
					} 
					else{
						usage() ;
					}
				}
				else{
					usage() ;	
				}

			}
			if (argc == 5){
				inpF = fopen(*argv, "r") ;
				if (inpF == NULL){
					fprintf(stderr, "File could not be opened\n") ;
					exit(0) ;
				}	       
			}
			else{
				inpF = stdin ;
			}
		}

	}



	// Command line parsing done, now call respective methods

	if (choice == 1){
		FILE *fp ;
		fp = fopen(tablefile, "r") ;
		if(fp == NULL){
			fprintf(stderr, "File could not be opened\n") ;
			exit(0) ;
		}
		Table::Instance()->LoadData(fp) ;
	}
	else if (choice == 2){
		if(strlen(poly1) != 8){
			fprintf(stderr, "Invalid length of poly1\n") ;
			exit(0) ;
		}
		if(strlen(poly2) != 8){
			fprintf(stderr, "Invalid length of poly1\n") ;
			exit(0) ;
		}
		GF28 p1(poly1) ;
		GF28 p2(poly2) ;
		GF28 res(poly1) ;
		unsigned char tempStr[4] ;
		p1.ModProd(p2, tempStr) ;
		res.copyW(tempStr) ;
		unsigned char resStr[17] ;
		p1.to_print(resStr) ;
		printf("%s CIRCLEX ", resStr) ;
		p2.to_print(resStr) ;
		printf("%s = ", resStr) ;
		res.to_print(resStr) ;
		printf("%s\n", resStr) ;

	}
	else if (choice == 3){
		FILE *fp ;
		fp = fopen(tablefile, "r") ;
		if(fp == NULL){
			fprintf(stderr, "File could not be opened\n") ;
			exit(0) ;
		}
		Table::Instance()->LoadData(fp) ;
		if ( strlen(key) != 32){
			fprintf(stderr, "Invalid key length\n") ;
			exit(0) ;
		}
		Word w(key, 16) ;
		Keys k(w) ;
		k.display() ;
	}
	else if (choice == 4){
		FILE *fp ;
		fp = fopen(tablefile, "r") ;
		if(fp == NULL){
			fprintf(stderr, "File could not be opened\n") ;
			exit(0) ;
		}
		Table::Instance()->LoadData(fp) ;
		if ( strlen(key) != 32){
			fprintf(stderr, "Invalid key length\n") ;
			exit(0) ;
		}
		Word w(key, 16) ;
		Keys k(w) ;
		unsigned char inp[17];
		int numbytes = fread(inp,1, 16, inpF) ;
		if (numbytes < 16){
			fprintf(stderr, "File size less than 16 bytes\n") ;
			exit(0) ;
		}
		char tempInp[32] ;
		for(int oo = 0 ; oo < 16 ; ++oo){
			sprintf((char *)&tempInp[oo*2], "%02x", inp[oo]) ;
		}
		EncryptOneBlock(tempInp, k) ;
	}
	else if (choice == 5){
		FILE *fp ;
		fp = fopen(tablefile, "r") ;
		if(fp == NULL){
			fprintf(stderr, "File could not be opened\n") ;
			exit(0) ;
		}
		Table::Instance()->LoadData(fp) ;
		if ( strlen(key) != 32){
			fprintf(stderr, "Invalid key length\n") ;
			exit(0) ;
		}
		Word w(key, 16) ;
		Keys k(w) ;
		unsigned char inp[17];
		int numbytes = fread(inp,1, 16, inpF) ;
		if (numbytes < 16){
			fprintf(stderr, "File size less than 16 bytes\n") ;
			exit(0) ;
		}
		char tempInp[32] ;
		for(int oo = 0 ; oo < 16 ; ++oo){
			sprintf((char *)&tempInp[oo*2], "%02x", inp[oo]) ;
		}
		DecryptOneBlock(tempInp, k) ;
	}
	else if (choice == 6){
		if(strlen(poly1) != 8){
			fprintf(stderr, "Invalid poly size\n") ;
			exit(0) ;
		}
		Word w(poly1, 4) ;
		w.Inverse() ;
	}








//	FILE *fp ;
//	fp = fopen("aes.in", "r") ;
//	Table::Instance()->LoadData(fp) ;
//	Word w("000102030405060708090a0b0c0d0e0f", 16) ;
//	Keys k(w) ;
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
//	Word w1("03030102",4) ;
//	Word w2("9ad1",2) ;
//	w1.Inverse() ;


	return 0;
}
