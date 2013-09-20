all: demo

clean:
	rm -f demo *.o

demo: parity.o
	g++ -o demo parity.o

parity.o: parity.cc
	g++ -c -Wall parity.cc -o parity.o

