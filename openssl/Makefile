CC=g++
CFLAGS=-g -W -Wall
LIBS=-lcrypto

BINARY=aes md5 md5_1 rsa dh evp_digest

all:$(BINARY)
.PHONY: all clean

aes: aes.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

md5: md5.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

md5_1: md5_1.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

rsa: rsa.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

dh: dh.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

evp_digest: evp_digest.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -f $(BINARY) *~ *flymake*
