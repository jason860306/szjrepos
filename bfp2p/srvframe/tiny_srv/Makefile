CC=g++
CFLAGS=-g -W -Wall -std=c++0x
COMMON_PATH=-I/home/szj0306/Documents/projects/p2p_server/branches/taishan/server/srvframe/include
COMMON_LIBS= -lsrvframe -lframecommon -lcrypto -lpthread -luuid `mysql_config --libs_r --include`
CPPUNIT_LIBS=-lcppunit
CPPUNIT_LIBS+=$(COMMON_LIBS)
GTEST_LIBS=-lgtest_main
GTEST_LIBS+=$(COMMON_LIBS)

TARGET=tiny_srv udp_cli http_client
OBJECTS=tiny_srv timer_srv timeout_check_thd ontime_synthread tiny_class_factory \
	udp_recv_thd udp_proc_snd_thd tiny_cmd tcp_proc_thd tiny_isrc_online_cmd \
	tcp_recv_snd_task
OBJECT=$(OBJECTS:%=%.o)

.PHONY: all clean
all: $(TARGET)

tiny_srv: $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $@ $(COMMON_LIBS) $(COMMON_PATH)

udp_cli: udp_cli.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(COMMON_LIBS) $(COMMON_PATH)

http_client: http_client.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(COMMON_LIBS) $(COMMON_PATH)

$(OBJECT):
	@echo compiling $(@:%.o=%.cpp)
	$(CC) $(CFLAGS) $(COMMON_PATH) -c $(@:%.o=%.cpp)

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJECT)
	@rm -f *~
	@rm -f *flymake*
