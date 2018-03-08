### Makefile --- rtmfp

## Author: szj0306@test1
## Version: $Id: Makefile,v 0.0 2013/06/09 03:17:32 szj0306 Exp $
## Keywords: 
## X-URL: 

CC=g++44
FLAGS=-g -W -Wall -std=c++0x
INCLUDE_PATH=-I/home/szj0306/Documents/boost/boost-trunk/ -I./src
LIBS_PATH=-L/home/szj0306/Documents/boost/boost-trunk/stage/lib -L./lib -Wl,-rpath,/home/szj0306/Documents/boost/boost-trunk/stage/lib
LIBS=-Wl,-Bstatic -lrtmfp -Wl,-Bdynamic -lboost_system -lpthread -lcrypto

OBJS=$(patsubst %.cpp, %.o, $(wildcard ./src/*.cpp))
LIBRARY=./lib/librtmfp.a
BINARY=./test/t_vlu_imp ./test/t_option_imp ./test/t_ihello_chunk_imp ./test/t_packet_imp rtmfpcli
#$(basename $(wildcard *.cpp))
#$(notdir $(wildcard ./src/*.cpp))

all: $(OBJS) $(LIBRARY) $(BINARY)
.PHONY: all clean

./src/%.o: ./src/%.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(FLAGS) -c $< -o $@

$(LIBRARY): $(OBJS)
	ar rcs $@ $^

./test/t_vlu_imp: ./test/t_vlu_imp.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

./test/t_option_imp: ./test/t_option_imp.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

./test/t_ihello_chunk_imp: ./test/t_ihello_chunk_imp.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

./test/t_packet_imp: ./test/t_packet_imp.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

rtmfpcli: rtmfpcli.cpp
	$(CC) $(FLAGS) $(INCLUDE_PATH) $(LIBS_PATH) $(LIBS) $^ $(LIBRARY) -o $@

clean:
	@rm -rf $(BINARY) $(LIBRARY) $(OBJS) *~ ./test/*~ ./src/*~

### Makefile ends here
