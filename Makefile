CC=g++
CFLAGS=-std=c++11 -O2 -Wall -Werror
LD=g++
LFLAGS=

all: book user library main link

book: book.cpp
	$(CC) $(CFLAGS) -o book.o -c book.cpp
    
user: user.cpp
	$(CC) $(CFLAGS) -o user.o -c user.cpp
    
library: library.cpp
	$(CC) $(CFLAGS) -o library.o -c library.cpp
	
main: main.cpp
	$(CC) $(CFLAGS) -o main.o -c main.cpp
	
link: main.o book.o user.o library.o
	$(LD) $(LFLAGS) -o library main.o book.o user.o library.o

clean: binaries docClean

binaries:
	rm -f library *.o
	
docClean:
	make clean -C latex/

doc: doxygen pdf

doxygen:
	doxygen doxygen.conf

pdf:
	make -C latex/