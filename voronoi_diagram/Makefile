CC = g++
CFLAGES = -g
CPPFLAGES = -Wall -pedantic

EXE = main

.PHONY: clean all

all: $(EXE)

main: main.cpp RBTree.o

RBTree.o: RBTree.cpp RBTree.h

clean:
	$(RM) *.o $(EXE)
