### Makefile --- rtmfp

## Author: szj0306@test1
## Version: $Id: Makefile,v 0.0 2013/06/09 03:17:32 szj0306 Exp $
## Keywords: 
## X-URL: 

CC=g++44
FLAGS=-g -std=c++0x#-W -Wall
INCLUDE_PATH=
LIBS_PATH=
LIBS=-Wl,-Bstatic -Wl,-Bdynamic -lpthread

OBJS=$(patsubst %.cpp, %.o, $(wildcard ./*.cpp))
LIBRARY=libmp4.a
BINARY=mp4parser
#$(basename $(wildcard *.cpp))
#$(notdir $(wildcard ./*.cpp))

all: $(OBJS) $(LIBRARY) $(BINARY)
.PHONY: all clean

%.o: %.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(FLAGS) -c $< -o $@

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

mp4parser: mp4parser.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

clean:
	@rm -rf $(BINARY) $(LIBRARY) $(OBJS) *~

### Makefile ends here
