CC=/usr/bin/gcc

all: main.pic.s main.nopic.s
	diff main.pic.s main.nopic.s

main.pic.s: main.c
	$(CC) -S -fpic main.c -o main.pic.s

main.nopic.s: main.c
	$(CC) -S -fno-pic main.c -o main.nopic.s
clean:
	rm -f *.s

