CC=g++
CFLAGS=-g -W -Wall
LIBS=

all: hash

hash: hash.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY: clean
clean:
	@rm -f hash
	@rm *~
