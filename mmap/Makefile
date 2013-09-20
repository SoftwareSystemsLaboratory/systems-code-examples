#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall

all: producer consumer

producer: producer.o
	$(CC) $(LINKFLAGS) -o producer producer.o

consumer: consumer.o
	$(CC) $(LINKFLAGS) -o consumer consumer.o

producer.o: producer.cc
	$(CC) $(CFLAGS) -c producer.cc -o producer.o

consumer.o: consumer.cc
	$(CC) $(CFLAGS) -c consumer.cc -o consumer.o

clean:
	rm -f *.o producer consumer shared.dat

