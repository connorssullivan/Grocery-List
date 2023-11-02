CFLAGS=-c -Wall
CC=g++
all: PROG

PROG: main.o LinkFun.o
	$(CC) main.o LinkFun.o -o PROG

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

LinkFun.o: LinkFun.cpp
	$(CC) $(CFLAGS) LinkFun.cpp

clean:
	rm -rf *.o PROG
rebuild:
	clean all
