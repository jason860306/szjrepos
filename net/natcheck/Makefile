CC=gcc
FLAGS=-g -W -Wall
LIBS=

TARGET=nccli ncsrv
all: $(TARGET)

.PHONY: all clean

nccli: nccli.c natcheck.c
	$(CC) $(FLAGS) $^ -o $@

ncsrv: ncsrv.c natcheck.c
	$(CC) $(FLAGS) $^ -o $@

clean:
	@rm -vf $(TARGET) *~ *flymake*
