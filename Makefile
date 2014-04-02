CC=g++ 
LEDAROOT=/usr/local/LEDA
INCLUDEDIR=$(LEDAROOT)/incl
CPPFLAGS=-Wall -O2 -fno-strict-aliasing
LIBX11=/usr/X11R6/lib64/

all: main

main: main.o 
		$(CC) -o main main.o -L$(LEDAROOT) -L$(LIBX11) -lX11 -lleda -lm 

main.o: main.cpp
		$(CC) -c main.cpp -I$(INCLUDEDIR) $(CPPFLAGS)
