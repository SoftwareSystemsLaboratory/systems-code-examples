#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall -lpthread -pthread

all: demo

demo: main.o lock.o
	$(CC) $(LINKFLAGS) -o demo main.o lock.o

lock.o: lock.cc lock.hh
	$(CC) $(CFLAGS) -c lock.cc -o lock.o

main.o: main.cc lock.hh
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm -f *.o demo

