### Makefile --- 

## Author: szj0306@test1
## Version: $Id: Makefile,v 0.0 2013/11/01 04:35:35 szj0306 Exp $
## Keywords: 
## X-URL: 

CC=gcc
FLAGS=-g -W -Wall
INCLUDE_PATH=
LIBS_PATH=
LIBS=-lpthread -lcrypto

OBJS=$(patsubst %.c, %.o, $(wildcard ./*.c))
LIBRARY= libmapsrv.a
BINARY= mapsrv
#$(basename $(wildcard *.cpp))
#$(notdir $(wildcard ./src/*.cpp))

all: $(OBJS) $(LIBRARY) $(BINARY)
.PHONY: all clean

./%.o: ./%.c
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(FLAGS) -c $< -o $@

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

mapsrv: main.c
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

clean:
	@rm -rf $(BINARY) $(LIBRARY) $(OBJS) *~

### Makefile ends here
