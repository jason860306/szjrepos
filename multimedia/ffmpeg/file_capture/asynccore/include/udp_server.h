///////////////////////////////////////////////////////////////////////////////
// udp_server.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "inet_address.h"
#include "socket.h"

struct event;

///////////////////////////////////////////////////////////////////////////////
// udp_server

class udp_server
{
public:
	typedef std::tr1::function<void (void *packet_buffer, int packet_size,
		const inet_address& remote_addr)> recv_packet_callback;

public:
	udp_server(int local_port);
	virtual ~udp_server();

	void start();
	void stop();

	void send_packet(const inet_address& dest_addr, void *packet_buffer, int packet_size);
	void set_recv_packet_callback(const recv_packet_callback& callback);

private:
	void open_socket();
	void close_socket();

	void read_cb();
	static void read_cb(socket_t fd, short what, void *arg);

private:
	udp_socket _socket;
	int _local_port;
	recv_packet_callback _recv_data_callback;
	event *_read_event;
};
