///////////////////////////////////////////////////////////////////////////////
// timer.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "classes.h"

struct event;
struct event_base;

///////////////////////////////////////////////////////////////////////////////
// timer

class timer
{
public:
	timer(TIMER_ID timer_id, INT64 milliseconds, bool repeat, const timer_callback& callback);
	~timer();

	TIMER_ID get_timer_id() const { return _timer_id; }
	bool is_repeat() const { return _repeat; }

private:
	void add_timer();
	void fill_timeval(timeval& tv, INT64 milliseconds);
	void invoke_callback();

	static void timer_cb(socket_t fd, short what, void *arg);

private:
	TIMER_ID _timer_id;
	timeval _tv;
	bool _repeat;
	timer_callback _callback;
	event *_ev;
};

///////////////////////////////////////////////////////////////////////////////
// timer_manager

class timer_manager : public singleton<timer_manager>
{
public:
	~timer_manager();

	TIMER_ID add_timer(INT64 milliseconds, bool repeat, const timer_callback& callback);
	void delete_timer(TIMER_ID timer_id);
	void delete_all_timers();

private:
	void register_timer(timer *timer);
	void unregister_timer(timer *timer);

private:
	friend class singleton<timer_manager>;
	friend class timer;

	typedef map<TIMER_ID, timer*> timer_map;

	timer_map _timers;
	seq_num_generator<INT64> _timer_id_gen;
	mutex _mutex;
};
