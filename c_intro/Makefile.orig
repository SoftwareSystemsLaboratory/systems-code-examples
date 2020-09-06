#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall

all: demo

demo: list.o main.o tests.o debug.o
	$(CC) $(LINKFLAGS) -o demo list.o main.o tests.o debug.o

debug.o: debug.cc debug.hh
	$(CC) $(CFLAGS) -c debug.cc -o debug.o

tests.o: tests.cc debug.hh list.hh
	$(CC) $(CFLAGS) -c tests.cc -o tests.o

list.o: list.hh list.cc debug.hh
	$(CC) $(CFLAGS) -c list.cc -o list.o

main.o: main.cc list.hh debug.hh tests.hh
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm -f *.o demo

