#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall

all: demo

demo: main.o
	$(CC) $(LINKFLAGS) -o demo main.o

main.o: main.cc
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm -f *.o demo

