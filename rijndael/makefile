# Example Makefile for the optimised ANSI C Rijndael code
# v3.0 

CFLAGS=-Wall -g -DTRACE_KAT_MCT -DINTERMEDIATE_VALUE_KAT -I.

all: rijndael-test-fst rijndael_enc rijndael_dec
PHONY: all clean

rijndael-test-fst:	rijndael-test-fst.o rijndael-api-fst.o rijndael-alg-fst.o

rijndael_enc: rijndael_enc.o rijndael.o
rijndael_dec: rijndael_dec.o rijndael.o

clean:
	@rm -rf *.o *.exe *~