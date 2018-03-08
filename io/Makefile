CC=gcc
# CC=clang
CFLAGS=-g -W -Wall #-std=gnu++0x
COMMON_LIBS=-lpthread

TARGET=multi_thd_demo
#c011_lambda
all: $(TARGET)

multi_thd_demo: multi_thd_demo.c
	$(CC) $(CFLAGS) $(COMMON_LIBS) $^ -o $@

.PHONY: all clean
clean:
	@rm -f $(TARGET)
	@rm -f *.o
	@rm -f *~
	@rm -f *flymake*
