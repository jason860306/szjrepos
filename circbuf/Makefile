CC=gcc
AR=ar
CFLAGS=-Wall -pedantic -ansi -g

lib: lib/circbuf.c lib/circbuf.o
	$(AR) rcs libcircbuf.a lib/circbuf.o

examples: app/hello.c app/hello-thread.c app/numbers.c
	$(CC) -o app/hello -Ilib/ -L. app/hello.c -lcircbuf
	$(CC) -o app/numbers -Ilib/ -L. app/numbers.c -lcircbuf
	$(CC) -o app/hello-thread -Ilib/ -L. app/hello-thread.c -lcircbuf -lpthread -lncurses

clean:
	@rm -rf libcircbuf.a lib/*.o *~ lib/*~ app/*~ doc/*~ doc/diagrams/*~