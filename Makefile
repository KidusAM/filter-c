# Compilation flags
CC = gcc

LDLIBS = -lm

CFLAGS = -g -Wall

LDFLAGS = -g

#End of compilation flags

filter: filter.o helpers.o

filter.o: filter.c bmp.h

helpers.o: helpers.c helpers.h

.PHONY: clean
clean:
	rm -f *.o a.out core speller

.PHONY: all
all: clean speller
