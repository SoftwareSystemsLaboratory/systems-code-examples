#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall -lpthread

all: demo

demo: main.o mutex.o trans.o
	$(CC) $(LINKFLAGS) -o demo main.o mutex.o trans.o

trans.o: trans.cc trans.hh mutex.hh
	$(CC) $(CFLAGS) -c trans.cc -o trans.o

mutex.o: mutex.cc mutex.hh
	$(CC) $(CFLAGS) -c mutex.cc -o mutex.o

main.o: main.cc mutex.hh trans.hh
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm -f *.o demo

