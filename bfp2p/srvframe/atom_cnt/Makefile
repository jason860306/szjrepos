CC=g++
CFLAGS=-g -W -Wall -std=c++0x
COMMON_PATH=-I/home/szj0306/Documents/projects/p2p_server/branches/taishan/server/srvframe/include \
`mysql_config --include`
COMMON_LIBS= -lsrvframe -lframecommon -lcrypto -lpthread -luuid `mysql_config --libs_r`

TARGET=fastcnt
OBJECTS=fastcnt
OBJECT=$(OBJECTS:%=%.o)

.PHONY: all clean
all: $(TARGET)

fastcnt: $(OBJECT)
	$(CC) $(CFLAGS) $^ -o $@ $(COMMON_LIBS) $(COMMON_PATH)

$(OBJECT):
	@echo compiling $(@:%.o=%.cpp)
	$(CC) $(CFLAGS) $(COMMON_LIBS) $(COMMON_PATH) -c $(@:%.o=%.cpp)

clean:
	@rm -f $(TARGET)
	@rm -f $(OBJECT)
	@rm -f *~
	@rm -f *flymake*
