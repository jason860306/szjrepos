///////////////////////////////////////////////////////////////////////////////
// exceptions.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "exception_msgs.h"

///////////////////////////////////////////////////////////////////////////////
/// class base_exception - The base class for exception

class base_exception : std::exception
{
public:
	base_exception() {}
	virtual ~base_exception() throw() {}

	virtual const char* what() const throw();
	virtual string get_error_message() const { return ""; }
	virtual string make_log_str() const;
private:
	mutable string what_;
};

///////////////////////////////////////////////////////////////////////////////
/// simple_exception - Simple exception

class simple_exception : public base_exception
{
public:
	simple_exception() : src_line_number_(-1) {}
	simple_exception(const char *error_msg,
		const char *src_file_name = NULL,
		int src_line_number = -1);
	virtual ~simple_exception() throw() {}

	virtual string get_error_message() const { return error_msg_; }
	virtual string make_log_str() const;
	void set_error_messsage(const char *msg) { error_msg_ = msg; }

protected:
	string error_msg_;
	string src_file_name_;
	int src_line_number_;
};

///////////////////////////////////////////////////////////////////////////////
/// memory_exception - Memory exception

class memory_exception : public simple_exception
{
public:
	memory_exception() {}
	explicit memory_exception(const char *error_msg) : simple_exception(error_msg) {}
	virtual ~memory_exception() throw() {}
};

///////////////////////////////////////////////////////////////////////////////
/// stream_exception - Stream exception

class stream_exception : public simple_exception
{
public:
	stream_exception() {}
	explicit stream_exception(const char *error_msg) : simple_exception(error_msg) {}
	virtual ~stream_exception() throw() {}
};

///////////////////////////////////////////////////////////////////////////////
/// file_exception - File exception

class file_exception : public simple_exception
{
public:
	file_exception() : error_code_(0) {}
	file_exception(const char *file_name, int error_code, const char *error_msg = NULL);
	virtual ~file_exception() throw() {}
protected:
	string file_name_;
	int error_code_;
};

///////////////////////////////////////////////////////////////////////////////
// socket_exception - Socket exception

class socket_exception : public simple_exception
{
public:
	socket_exception() {}
	explicit socket_exception(const char *error_msg) : simple_exception(error_msg) {}
	virtual ~socket_exception() throw() {}
};

///////////////////////////////////////////////////////////////////////////////
// Exception throwing rountines.

#define THROW_EXCEPTION(msg)  throw_exception(msg, __FILE__, __LINE__)

/// Throws a simple_exception exception.
inline void throw_exception(const char *msg,
	const char *src_file_name = NULL, int src_line_number = -1)
{
	throw simple_exception(msg, src_file_name, src_line_number);
}

/// Throws a memory_exception exception.
inline void throw_memory_exception()
{
	throw memory_exception(SEM_OUT_OF_MEMORY);
}

/// Throws a stream_exception exception.
inline void throw_stream_exception(const char *msg)
{
	throw stream_exception(msg);
}

/// Throws a file_exception exception.
inline void throw_file_exception(const char *file_name, int error_code,
	const char *error_msg = NULL)
{
	throw file_exception(file_name, error_code, error_msg);
}

/// Throws a socket_exception exception.
inline void throw_socket_exception(const char *msg)
{
	throw socket_exception(msg);
}

///////////////////////////////////////////////////////////////////////////////
