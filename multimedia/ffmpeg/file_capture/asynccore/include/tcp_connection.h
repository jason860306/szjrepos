///////////////////////////////////////////////////////////////////////////////
// tcp_connection.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "inet_address.h"

struct bufferevent;

///////////////////////////////////////////////////////////////////////////////
// tcp_connection

class tcp_connection
{
public:
	enum DISCONNECT_REASON
	{
		DR_EOF = 0,
		DR_ERROR = 1,
		DR_READ_ERROR = 2,
		DR_WRITE_ERROR = 3,
	};

	typedef std::tr1::function<void (tcp_connection *connection)> connected_callback;
	typedef std::tr1::function<void (tcp_connection *connection, int reason)> disconnected_callback;
	typedef std::tr1::function<void (tcp_connection *connection, int readable_bytes)> readable_callback;
	typedef std::tr1::function<void (tcp_connection *connection)> writeable_callback;

public:
	tcp_connection();
	virtual ~tcp_connection();

	virtual void disconnect();

	virtual int peek(char *buffer, int size);
	virtual int read(char *buffer, int size);
	virtual bool write(const char *buffer, int size);

	virtual inet_address get_local_addr();
	virtual inet_address get_remote_addr();

	void set_connected_callback(const connected_callback& callback);
	void set_disconnected_callback(const disconnected_callback& callback);
	void set_readable_callback(const readable_callback& callback);
	void set_writeable_callback(const writeable_callback& callback);

	bool assign(socket_t fd);

protected:
	void close();

	static void read_cb(bufferevent *bev, void *ptr);
	static void write_cb(bufferevent *bev, void *ptr);
	static void event_cb(bufferevent *bev, short events, void *ptr);

private:
	void read_cb();
	void write_cb();
	void event_cb(short events);

protected:
	bufferevent *_bev;

	connected_callback _connected_callback;
	disconnected_callback _disconnected_callback;
	readable_callback _readable_callback;
	writeable_callback _writeable_callback;
};
