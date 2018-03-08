CC=g++
CFLAGS=-g -W -Wall
LIBS=-lpthread

TARGET=test_timer

all: $(TARGET)
.PHONY: all clean

test_timer: test_timer.cpp thread.cpp timer_thread.cpp
	$(CC) $(CFLAGS) $(LIBS) $^ -o $@

clean:
	@rm -f $(TARGET)
	@rm *~
