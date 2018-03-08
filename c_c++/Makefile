CC=g++
# CC=clang
CFLAGS=-g -O0 -W -Wall #-std=gnu++0x
COMMON_LIBS=
CPPUNIT_LIBS=
CPPUNIT_LIBS+=$(COMMON_LIBS)
GTEST_LIBS=
GTEST_LIBS+=$(COMMON_LIBS)

TARGET= ptr destructor defconstructor endian_independent val_invalid_read distance inherit
#c011_lambda
all: $(TARGET)

ptr: ptr.cpp
	$(CC) $(CFLAGS) $^ -o $@

destructor: destructor.cpp
	$(CC) $(CFLAGS) $^ -o $@

c011_lambda: c011_lambda.cpp
	$(CC) $(CFLAGS) $^ -o $@

defconstructor: defconstructor.cpp
	$(CC) $(CFLAGS) $^ -o $@

endian_independent: endian_independent.cpp
	g++ $(CFLAGS) $^ -o $@

distance: distance.cpp
	g++ $(CFLAGS) $^ -o $@

val_invalid_read: val_invalid_read.c
	$(CC) $(CFLAGS) $^ -o $@

inherit: inherit.cpp
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: all clean
clean:
	@rm -f $(TARGET)
	@rm -f *.o
	@rm -f *~
	@rm -f *flymake*
