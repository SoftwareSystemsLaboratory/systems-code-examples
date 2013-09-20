#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall -lpthread

all: demo

demo: main.o mutex.o monitor.o queue.o debug.o
	$(CC) $(LINKFLAGS) -o demo main.o mutex.o monitor.o queue.o debug.o

debug.o: debug.cc debug.hh
	$(CC) $(CFLAGS) -c debug.cc -o debug.o

queue.o: queue.cc queue.hh
	$(CC) $(CFLAGS) -c queue.cc -o queue.o

monitor.o: monitor.cc monitor.hh
	$(CC) $(CFLAGS) -c monitor.cc -o monitor.o

mutex.o: mutex.cc mutex.hh
	$(CC) $(CFLAGS) -c mutex.cc -o mutex.o

main.o: main.cc mutex.hh monitor.hh
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm -f *.o demo

