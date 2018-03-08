///////////////////////////////////////////////////////////////////////////////
// async_core.h
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include "global_defs.h"
#include "classes.h"
#include "thread.h"

struct event;
struct event_base;
struct evdns_base;

///////////////////////////////////////////////////////////////////////////////
// async_core

class async_core : public singleton<async_core>
{
public:
	~async_core();

	void start();
	void stop();

	bool is_started();

	void sync_run(const functor& func);
	void async_run(const functor& func);

	TIMER_ID run_after(INT64 delay, const timer_callback& callback);
	TIMER_ID run_every(INT64 interval, const timer_callback& callback);
	void cancel_timer(TIMER_ID timer_id);

	event_base* get_event_base() { return _event_base; }
	evdns_base* get_evdns_base() { return _evdns_base; }

private:
	async_core();

	void initialize();
	void finalize();

	void init_winsock();
	void init_evdns_base();

	void start_worker_thread();
	void stop_worker_thread();

	bool is_in_worker_thread();
	void wakeup();

	void process_sync_functors();
	void process_async_functors();

	void thread_proc(thread *thread);
	void handle_wakeup();

	static void wakeup_cb(socket_t fd, short what, void *arg);

private:
	friend class singleton<async_core>;
	friend class worker_thread;

	struct sync_functor_item
	{
		functor func;
		semaphore sem;
	};

private:
	event_base *_event_base;
	evdns_base *_evdns_base;
	event *_wakeup_event;
	thread *_worker_thread;
	mutex _mutex;

	vector<sync_functor_item*> _sync_functors;
	vector<functor> _async_functors;
};
