CC=g++ 
LEDAROOT=/usr/local/LEDA
INCLUDEDIR=$(LEDAROOT)/incl
CPPFLAGS=-Wall -O2 -Wno-deprecated -std=c++0x
LIBX11=/usr/X11R6/lib64/

all:  main

main: main.o hw02_functions.o
		$(CC) -o main main.o hw02_functions.o 

main.o: main.cpp hw02.h 
		$(CC) -c main.cpp -I$(CPPFLAGS)

hw02_functions.o: hw02_functions.cpp hw02.h
		$(CC) -c -o $@ hw02_functions.cpp -I$(CPPFLAGS)

clean:
	rm -rf *.o main
