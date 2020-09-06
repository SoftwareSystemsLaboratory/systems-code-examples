
all: demo

clean:
	rm -f *.o demo

demo: demo.o malloc.o
	g++ demo.o malloc.o -o demo

demo.o: demo.cc malloc.h
	g++ -c demo.cc -o demo.o

malloc.o: malloc.cc malloc.h
	g++ -c malloc.cc -o malloc.o

