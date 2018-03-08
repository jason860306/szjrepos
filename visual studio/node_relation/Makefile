### Makefile ---

## Author: szj0306@szj0306.localhost.localdomain
## Version: $Id: Makefile,v 0.0 2014/04/03 15:22:45 szj0306 Exp $
## Keywords:
## X-URL:
CC=g++
FLAGS=-g -W -Wall -O0
Targe=node_relation
All: $(Targe)

node_relation: node_relation.cpp
	$(CC) $(FLAGS) $< -o $@

.PHONY: clean
clean:
	@rm -rf *.o *~ $(Targe)

### Makefile ends here