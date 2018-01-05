CC = gcc

CSAPP_INC = ../../../include
CSAPP_SRC = ../../../src

CFLAGS = -O2 -Wall -I $(CSAPP_INC) -I .
LDLIBS = -lpthread

all: dictionary  multiplier

dictionary: dictionary.c
	$(CC) $(CFLAGS) dictionary.c $(CSAPP_SRC)/csapp.o $(LDLIBS) -o dictionary

multiplier: multiplier.c
	$(CC) $(CFLAGS) -o multiplier multiplier.c
clean:
	rm -f adder *~
