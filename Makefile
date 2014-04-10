CC=g++ 
LEDAROOT=/usr/local/LEDA
INCLUDEDIR=$(LEDAROOT)/incl
CPPFLAGS=-Wall -O2 -fno-strict-aliasing
LIBX11=/usr/X11R6/lib64/

all:  main

main: main.o hw01_functions.o
		$(CC) -o main main.o hw01_functions.o -L$(LEDAROOT) -L$(LIBX11) -lX11 -lleda -lm 

main.o: main.cpp hw01.h 
		$(CC) -c main.cpp -I$(INCLUDEDIR) $(CPPFLAGS)

hw01_functions.o: hw01_functions.cpp hw01.h
		$(CC) -c -o $@ hw01_functions.cpp -I$(INCLUDEDIR) $(CPPFLAGS)

clean:
	rm -rf *.o main
