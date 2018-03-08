///////////////////////////////////////////////////////////////////////////////
// socket.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "classes.h"
#include "inet_address.h"

///////////////////////////////////////////////////////////////////////////////
// socket

class socket : noncopyable
{
public:
	socket();
	virtual ~socket();

	virtual void open();
	virtual void close();

	void bind(UINT16 port);

	bool is_active() const { return _is_active; }
	socket_t get_handle() const { return _handle; }
	inet_address get_local_addr() const;
	inet_address get_remote_addr() const;
	bool is_block_mode() const { return _is_block_mode; }
	void set_block_mode(bool value);
	void set_handle(socket_t value);

	static inet_address get_socket_local_addr(socket_t handle);
	static inet_address get_socket_remote_addr(socket_t handle);

protected:
	void set_active(bool value);
	void set_domain(int value);
	void set_type(int value);
	void set_protocol(int value);

	int get_last_error();
	string get_last_error_msg();
	void throw_socket_last_error();

private:
	void do_set_block_mode(socket_t handle, bool value);
	void do_close();

protected:
	bool _is_active;     // 套接字是否准备就绪
	socket_t _handle;      // 套接字句柄
	int _domain;         // 套接字的协议家族 (PF_UNIX, PF_INET, PF_INET6, PF_IPX, ...)
	int _type;           // 套接字类型，必须指定 (SOCK_STREAM, SOCK_DGRAM, SOCK_RAW, SOCK_RDM, SOCK_SEQPACKET)
	int _protocol;       // 套接字所用协议，可为0 (IPPROTO_IP, IPPROTO_UDP, IPPROTO_TCP, ...)
	bool _is_block_mode; // 是否为阻塞模式 (缺省为阻塞模式)
};

///////////////////////////////////////////////////////////////////////////////
// udp_socket

class udp_socket : public socket
{
public:
	udp_socket()
	{
		_type = SOCK_DGRAM;
		_protocol = IPPROTO_UDP;
		_is_block_mode = true;
	}

	int recv_data(void *buffer, int size);
	int recv_data(void *buffer, int size, inet_address& remote_addr);
	int send_data(void *buffer, int size, const inet_address& remote_addr);

	virtual void open();
};

///////////////////////////////////////////////////////////////////////////////
// tcp_socket

class tcp_socket : public socket
{
public:
	tcp_socket()
	{
		_type = SOCK_STREAM;
		_protocol = IPPROTO_TCP;
		_is_block_mode = false;
	}

	void shutdown(bool close_send = true, bool close_recv = true);
};
