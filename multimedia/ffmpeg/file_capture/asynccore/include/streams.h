///////////////////////////////////////////////////////////////////////////////
// streams.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "classes.h"
#include "exceptions.h"

///////////////////////////////////////////////////////////////////////////////
// stream

enum SEEK_ORIGIN
{
	SO_BEGINNING    = 0,
	SO_CURRENT      = 1,
	SO_END          = 2
};

class stream
{
public:
	virtual ~stream() {}

	virtual int read(void *buffer, int count) = 0;
	virtual int write(const void *buffer, int count) = 0;
	virtual INT64 seek(INT64 offset, SEEK_ORIGIN seek_origin) = 0;

	void read_buffer(void *buffer, int count);
	void write_buffer(const void *buffer, int count);

	INT64 get_position() { return seek(0, SO_CURRENT); }
	void set_position(INT64 pos) { seek(pos, SO_BEGINNING); }

	virtual INT64 get_size();
	virtual void set_size(INT64 size) {}
};

///////////////////////////////////////////////////////////////////////////////
// memory_stream

class memory_stream : public stream
{
public:
	enum { DEFAULT_MEMORY_DELTA = 1024 };
	enum { MIN_MEMORY_DELTA = 256 };

public:
	explicit memory_stream(int memory_delta = DEFAULT_MEMORY_DELTA);
	memory_stream(const memory_stream& src);
	virtual ~memory_stream();

	memory_stream& operator = (const memory_stream& rhs);

	virtual int read(void *buffer, int count);
	virtual int write(const void *buffer, int count);
	virtual INT64 seek(INT64 offset, SEEK_ORIGIN seek_origin);
	virtual void set_size(INT64 size);
	bool load_from_stream(stream& stream);
	bool load_from_file(const string& file_name);
	bool save_to_stream(stream& stream);
	bool save_to_file(const string& file_name);
	void clear();
	char* get_memory() { return _memory; }

private:
	void init();
	void assign(const memory_stream& src);
	void set_memory_delta(int new_memory_delta);
	void set_pointer(char *memory, int size);
	void set_capacity(int new_capacity);
	char* realloc(int& new_capacity);

private:
	char *_memory;
	int _capacity;
	int _size;
	int _position;
	int _memory_delta;
};

///////////////////////////////////////////////////////////////////////////////
// file_stream

// file open mode
enum
{
	FM_CREATE           = 0xFFFF,
	FM_OPEN_READ        = 0x0000,
	FM_OPEN_WRITE       = 0x0001,
	FM_OPEN_READ_WRITE  = 0x0002,

	FM_SHARE_EXCLUSIVE  = 0x0010,
	FM_SHARE_DENY_WRITE = 0x0020,
	FM_SHARE_DENY_NONE  = 0x0040
};

// default file access rights
enum { DEFAULT_FILE_ACCESS_RIGHTS = 0 };

class file_stream :
	public stream,
	noncopyable
{
public:
	file_stream();
	file_stream(const string& file_name, UINT open_mode, UINT rights = DEFAULT_FILE_ACCESS_RIGHTS);
	virtual ~file_stream();

	bool open(const string& file_name, UINT open_mode,
		UINT rights = DEFAULT_FILE_ACCESS_RIGHTS, file_exception* exception = NULL);
	void close();

	virtual int read(void *buffer, int count);
	virtual int write(const void *buffer, int count);
	virtual INT64 seek(INT64 offset, SEEK_ORIGIN seek_origin);
	virtual void set_size(INT64 size);

	string get_file_name() const { return _file_name; }
	HANDLE get_handle() const { return _handle; }
	bool is_open() const;

private:
	void init();
	HANDLE file_create(const string& file_name, UINT rights);
	HANDLE file_open(const string& file_name, UINT open_mode);
	void file_close(HANDLE handle);
	int file_read(HANDLE handle, void *buffer, int count);
	int file_write(HANDLE handle, const void *buffer, int count);
	INT64 file_seek(HANDLE handle, INT64 offset, SEEK_ORIGIN seek_origin);

private:
	string _file_name;
	HANDLE _handle;
};
