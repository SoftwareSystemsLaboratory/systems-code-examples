#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall -lpthread -pthread

all: demo

demo: main.o mutex.o semaphore.o queue.o debug.o
	$(CC) $(LINKFLAGS) -o demo main.o mutex.o semaphore.o queue.o debug.o

queue.o: queue.cc queue.hh debug.hh
	$(CC) $(CFLAGS) -c queue.cc -o queue.o

debug.o: debug.cc debug.hh
	$(CC) $(CFLAGS) -c debug.cc -o debug.o

semaphore.o: semaphore.cc semaphore.hh mutex.hh
	$(CC) $(CFLAGS) -c semaphore.cc -o semaphore.o

mutex.o: mutex.cc mutex.hh
	$(CC) $(CFLAGS) -c mutex.cc -o mutex.o

main.o: main.cc mutex.hh
	$(CC) $(CFLAGS) -c main.cc -o main.o

clean:
	rm -f *.o demo

