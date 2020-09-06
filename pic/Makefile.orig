CC=/usr/bin/g++

all: main.pic.s main.s

main.pic.s: main.cc
	$(CC) -S -fpic main.cc -o main.pic.s

main.s: main.cc
	$(CC) -S main.cc -o main.s
clean:
	rm -f *.s

