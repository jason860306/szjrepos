CC=gcc
FLAGS=-g -W -Wall
LIBS=-letcp

TARGET=hb_client hb_server hb_client2 hb_server2 telemetrys telemetryc
all: $(TARGET)

.PHONY: all clean

hb_server: hb_server.c tcp_server.c set_address.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

hb_client: hb_client.c tcp_client.c set_address.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

hb_server2: hb_server2.c tcp_server.c set_address.c readn.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

hb_client2: hb_client2.c tcp_client.c set_address.c readn.c tcp_server.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

telemetrys: telemetrys.c tcp_server.c set_address.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

telemetryc: telemetryc.c tcp_client.c set_address.c
	$(CC) $(FLAGS) $(LIBS) $^ -o $@

clean:
	@rm -vf $(TARGET) *~ *flymake*
