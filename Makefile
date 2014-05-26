CC=g++ 
LEDAROOT=/usr/local/LEDA
INCLUDEDIR=$(LEDAROOT)/incl
CPPFLAGS=-Wall -O2 -fno-strict-aliasing -std=c++0x
LIBX11=/usr/X11R6/lib64/

all:  main

main: main.o hw02_functions.o
		$(CC) -o main main.o hw02_functions.o -L$(LEDAROOT) -L$(LIBX11) -lX11 -lleda -lm

main.o: main.cpp hw02.h 
		$(CC) -c main.cpp I$(INCLUDEDIR) $(CPPFLAGS)

hw02_functions.o: hw02_functions.cpp hw02.h
		$(CC) -c -o $@ hw02_functions.cpp -I$(INCLUDEDIR) $(CPPFLAGS)

clean:
	rm -rf *.o main
