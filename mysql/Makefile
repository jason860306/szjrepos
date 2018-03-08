CC=gcc
FLAGS=-g -W -Wall -O0
LIBS=`mysql_config --cflags --libs`
TARGET=test_libmysqld version createdb createtables querytables testdatetime
all: $(TARGET)
.PHONY: all clean

test_libmysqld: test_libmysqld.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

version: version.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

createdb: createdb.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

createtables: createtables.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

querytables: querytables.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

testdatetime: testdatetime.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

clean:
	rm -f $(TARGET)
	rm -f *~

