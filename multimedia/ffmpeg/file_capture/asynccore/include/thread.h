///////////////////////////////////////////////////////////////////////////////
// thread.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "classes.h"

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

///////////////////////////////////////////////////////////////////////////////

class thread;
class semaphore;
class win_thread_impl;

///////////////////////////////////////////////////////////////////////////////
// type defines

// thread priority
enum
{
	THREAD_PRI_IDLE         = 0,
	THREAD_PRI_LOWEST       = 1,
	THREAD_PRI_NORMAL       = 2,
	THREAD_PRI_HIGHER       = 3,
	THREAD_PRI_HIGHEST      = 4,
	THREAD_PRI_TIMECRITICAL = 5
};

///////////////////////////////////////////////////////////////////////////////
// thread

class thread : noncopyable
{
public:
	typedef std::tr1::function<void (thread& thread)> thread_proc;

public:
	thread();
	virtual ~thread();

	/// Create a thread and run it immediately.
	static thread* create(const thread_proc& thread_proc);

	/// Run the thread.
	void run();

	/// Notify the thread to exit.
	void terminate();

	/// Wait for the thread to exit, and return the exit code of the thread.
	int wait_for();

	/// Indicate whether the thread is running.
	bool is_running();

	THREAD_ID get_thread_id() const;
	int is_terminated() const;
	int get_return_value() const;
	bool is_auto_delete() const;
	int get_term_elapsed_secs() const;
	int get_priority() const;

	void set_terminated(bool value);
	void set_return_value(int value);
	void set_auto_delete(bool value);
	void set_priority(int value);

protected:
	virtual void execute() { if (_thread_proc) _thread_proc(*this); }
	virtual void after_execute() {}
	virtual void before_terminate() {}

private:
	win_thread_impl *_thread_impl;
	thread_proc _thread_proc;

	friend class thread_impl;
};

///////////////////////////////////////////////////////////////////////////////
