#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall

all: server client

server: server.o
	$(CC) $(LINKFLAGS) -o server server.o

server.o: server.cc
	$(CC) $(CFLAGS) -c server.cc -o server.o

client: client.o
	$(CC) $(LINKFLAGS) -o client client.o

client.o: client.cc
	$(CC) $(CFLAGS) -c client.cc -o client.o

clean:
	rm -f *.o client server

