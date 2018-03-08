### Makefile --- 

## Author: szj0306@test1
## Version: $Id: Makefile,v 0.0 2013/09/23 03:03:54 szj0306 Exp $
## Keywords: 
## X-URL:

CC=gcc
FLAGS=-g -W -Wall -O0
INCPATH=-I/usr/src/kernels/`uname -r`-`uname -i`/include
LIBPATH=
LIBS=

OBJ=kmalloc_demo
All: $(OBJ)

kmalloc_demo: kmalloc_demo.c
	$(CC) $(FLAGS) $(INCPATH) $(LIBPATH) $(LIBS) $^ -o $@

clean:
	rm -rf $(OBJ) *~

### Makefile ends here
