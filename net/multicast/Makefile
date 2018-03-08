### Makefile --- 

## Author: szj0306@bf.szj0306.localhost
## Version: $Id: Makefile,v 0.0 2013/02/25 07:28:42 szj0306 Exp $
## Keywords: 
## X-URL: 

CC=g++
FLAGS=-g -W -Wall
LIBS=

TARGET=multicastcli multicastsrv mcastclient mcastserver
all: $(TARGET)

.PHONY: all clean

multicastcli: multicastcli.cpp
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

multicastsrv: multicastsrv.cpp
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

mcastclient: mcastclient.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

mcastserver: mcastserver.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

clean:
	@rm -vf $(TARGET) *~ *flymake*

### Makefile ends here
