#CC=/usr/pkg/bin/g++
CC=/usr/bin/g++
CFLAGS= -g -Wall -I.
LINKFLAGS= -g -Wall 

all: producer consumer

producer: producer.o message.o
	$(CC) $(LINKFLAGS) -o producer producer.o message.o -lpthread -pthread

consumer: consumer.o message.o
	$(CC) $(LINKFLAGS) -o consumer consumer.o message.o -lpthread -pthread

message.o: message.cc message.hh
	$(CC) $(CFLAGS) -c message.cc -o message.o

producer.o: producer.cc message.hh
	$(CC) $(CFLAGS) -c producer.cc -o producer.o

consumer.o: consumer.cc message.hh
	$(CC) $(CFLAGS) -c consumer.cc -o consumer.o

clean:
	rm -f *.o producer consumer shared.dat

