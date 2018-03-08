### Makefile --- 

## Author: szj0306@test1
## Version: $Id: Makefile,v 0.0 2013/09/25 02:25:13 szj0306 Exp $
## Keywords: 
## X-URL: 

CC=gcc
FLAGS=-g -W -Wall -O0
INCPATH=
LIBPATH=
LIBS=-levent

OBJ=evtimer
All: $(OBJ)

evtimer: evtimer.c
	$(CC) $(FLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $^ -o $@

clean:
	rm -rf $(OBJ) *~

### Makefile ends here
