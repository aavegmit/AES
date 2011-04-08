# Macros

CC = g++
CFLAGS = -g -Wall
OBJ = main.o table.o keys.o word.o gf28.o byte.o block.o
LIBS = -lcrypto
#LIBS = -L/home.scf-22/csci551b/openssl/lib -lcrypto -lnsl -lsocket -lresolv
#INC = -I/home/scf-22/csci551b/openssl/include
INC = 

# Explicit rule
all: hw6 

hw6: $(OBJ)
	$(CC) $(CFLAGS) -o hw6 $(OBJ) $(INC) $(LIBS) 

clean:
	rm -rf *.o hw6

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc $(INC)
table.o: table.cc
	$(CC) $(CFLAGS) -c table.cc $(INC)
keys.o: keys.cc
	$(CC) $(CFLAGS) -c keys.cc $(INC)
word.o: word.cc word.h
	$(CC) $(CFLAGS) -c word.cc $(INC)
gf28.o: gf28.cc gf28.h word.h
	$(CC) $(CFLAGS) -c gf28.cc $(INC)
byte.o: byte.cc
	$(CC) $(CFLAGS) -c byte.cc $(INC)
block.o: block.cc
	$(CC) $(CFLAGS) -c block.cc $(INC)
