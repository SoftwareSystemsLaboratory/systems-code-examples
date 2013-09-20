CC=/usr/bin/g++
CFLAGS=-Wall -g
LDFLAGS=-Wall -g

all: test

test: main.o
	${CC} ${LDFLAGS} -o test main.o

main.o: main.cc
	${CC} ${CFLAGS} -c main.cc -o main.o

clean:
	rm -f *.o test

