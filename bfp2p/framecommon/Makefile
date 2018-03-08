CC=g++
CFLAGS=-g -W -Wall -std=c++0x
COMMON_PATH=-I/home/szj0306/Documents/projects/p2p_server/branches/taishan/server/srvframe/include -I/usr/include/mysql
COMMON_LIBS=-lsrvframe -lframecommon -lcrypto -lpthread -luuid `mysql_config --libs`
CPPUNIT_LIBS=-lcppunit
CPPUNIT_LIBS+=$(COMMON_LIBS)
GTEST_LIBS=-lgtest_main
GTEST_LIBS+=$(COMMON_LIBS)

TARGET=aes_gtest BufferHelperGTest cppunit_main frame_gtest_main BufferHelperCppUnitTest tiny_srv

all: $(TARGET)

aes_gtest: aes_gtest.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(GTEST_LIBS)

BufferHelperGTest: BufferHelperGTest.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(GTEST_LIBS)

frame_gtest_main: aes_gtest.cpp BufferHelperGTest.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(GTEST_LIBS)

cppunit_main:cppunit_main.cpp aes_cppunit.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(CPPUNIT_LIBS)

BufferHelperCppUnitTest: BufferHelperCppUnitTest.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(CPPUNIT_LIBS)

tiny_srv: tiny_srv.cpp timer_srv.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(COMMON_LIBS) $(COMMON_PATH)

# .PHONY: clean
clean:
	@rm -f $(TARGET)
	@rm -f *.o
	@rm -f *~
	@rm -f *flymake*
