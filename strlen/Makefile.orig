CC=/usr/bin/gcc

all: main

main: main.o
	$(CC) main.o -o main

main.o: main.c
	$(CC) -c main.c -o main.o

clean:
	rm -f main.o main

