# Makefile for mSweeper
#
# Ryan Hyun, July 2019

PROG = mSweeper
OBJS = mSweeper.o

CFLAGS = -W -Wall -pedantic -std=c++11
CC = g++
MAKE = make

all: mSweeper

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

indexer.o: mSweeper.cpp

.PHONY: clean

clean:
	rm -rf *.dSYM
	rm -f *~
	rm -f *.o
	rm -f $(PROG)
